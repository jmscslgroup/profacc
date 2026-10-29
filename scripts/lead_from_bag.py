#!/usr/bin/env python3
"""Lead car and radar for a simulated ego, replayed from a window of a car bag.

The ego plant (carcomplexsimulink) is Simulink-generated and steps on a
wall-clock timer, so it skips or bunches steps when the machine stalls. A lead
that advances on wall-clock time drifts against it (at 20 m/s a 0.25 s stall
moves the gap by 5 m), and so does any lead that guesses steps from message
timing. The plant publishes exactly msgs_per_step front_x messages per 0.05 s
step (3 for carcomplexsimulink), so this node counts them and runs in
lock-step with the plant:

  1. Pre-roll, until the plant publishes: it speaks for the ego
     (car/state/vel_x = v0) and the radar (lead_dist = gap0, rel_vel), so the
     whole chain (offset, controller, speed limiter, CBF) settles on the bag's
     real starting condition instead of on zeros. It sets ~ready once the bag
     is loaded; the launch file holds the plant back until then.
  2. On the last front_x of every plant step it advances the lead by one step,
     dt of bag time, and publishes the lead's speed and position and the
     radar's lead_dist (lead rear - ego front) and rel_vel (v_lead - v_ego) for
     that step. The first step puts the lead at front_x + gap0.
  3. After duration seconds of plant time it shuts down; launch it with
     required="true" so the whole simulation ends with it.

Publishes (remap as needed):
    leadcar/car/state/vel_x  std_msgs/Float64  lead speed from the bag (m/s)
    leadcar/odom_x           std_msgs/Float64  lead rear bumper position (m)
    lead_dist                std_msgs/Float64  bumper gap (m), the car's radar
    rel_vel                  std_msgs/Float64  v_lead - v_ego (m/s)
    acc/set_speed            std_msgs/Int16    the car's ACC set speed from the bag
    car/state/vel_x          std_msgs/Float64  ego speed v0, pre-roll only
    car/radar/track_a0..a15  geometry_msgs/PointStamped  only with ~tracks: the bag's
                             radar tracks, i.e. as seen from the LEAD (the car that
                             recorded the bag), each slot's latest message once per step
Subscribes (from the plant):
    front_x, car/state/vel_x std_msgs/Float64

Params (private):
    ~bag        path of the bag file
    ~start      seconds from the start of the bag where the window begins
    ~duration   window length in seconds of plant time (default 120)
    ~gap0       starting bumper gap (m); default: the bag's /lead_dist at start
    ~v0         the ego plant's initial speed; default: the bag speed at start
    ~dt         the plant's step (s, default 0.05)
    ~msgs_per_step  front_x messages the plant publishes per step (default 3)
    ~plant      the plant's node name (default /carcomplexsimulink)
    ~tracks     also replay the bag's /car/radar/track_a* (default false). The
                tracks are relative to the lead, so a node turning them into
                absolute speeds should read leadcar/car/state/vel_x.
"""
import bisect

import rosbag
import rospy
from geometry_msgs.msg import PointStamped
from std_msgs.msg import Float64, Int16

N_TRACKS = 16
TRACK = '/car/radar/track_a%d'


def window(bag_path, start, duration, tracks=False):
    """Return (speeds, set_speeds, lead_dists, track_slots): the first three are
    ([t...], [value...]), track_slots a list of ([t...], [msg...]) per radar slot
    (empty unless tracks), all with t in seconds from the start of the window."""
    out = {'/car/state/vel_x': ([], []), '/acc/set_speed': ([], []), '/lead_dist': ([], [])}
    if tracks:
        out.update({TRACK % k: ([], []) for k in range(N_TRACKS)})
    with rosbag.Bag(bag_path) as bag:
        t0 = bag.get_start_time()
        lo = rospy.Time.from_sec(t0 + start - 2.0)
        hi = rospy.Time.from_sec(t0 + start + duration + 1.0)
        for topic, msg, t in bag.read_messages(topics=list(out), start_time=lo, end_time=hi):
            out[topic][0].append(t.to_sec() - t0 - start)
            out[topic][1].append(msg if topic.startswith('/car/radar/') else msg.data)
    slots = [out[TRACK % k] for k in range(N_TRACKS)] if tracks else []
    return out['/car/state/vel_x'], out['/acc/set_speed'], out['/lead_dist'], slots


def at(series, t):
    """Latest value at or before t (zero-order hold, like the car's CAN data)."""
    times, values = series
    return values[max(bisect.bisect_right(times, t) - 1, 0)]


class LeadFromBag:
    def __init__(self):
        self.bag = rospy.get_param('~bag')
        self.start = rospy.get_param('~start')
        self.duration = rospy.get_param('~duration', 120.0)
        self.dt = rospy.get_param('~dt', 0.05)
        self.per_step = rospy.get_param('~msgs_per_step', 3)
        self.plant = rospy.get_param('~plant', '/carcomplexsimulink')
        self.speeds, self.set_speeds, lead_dists, self.slots = window(
            self.bag, self.start, self.duration, rospy.get_param('~tracks', False))
        if not self.speeds[0]:
            rospy.logfatal('no /car/state/vel_x in %s at %.1f s' % (self.bag, self.start))
            raise SystemExit(1)
        self.gap0 = rospy.get_param('~gap0', at(lead_dists, 0.0) if lead_dists[0] else 50.0)
        self.v0 = rospy.get_param('~v0', at(self.speeds, 0.0))

        self.lead_vel = rospy.Publisher('leadcar/car/state/vel_x', Float64, queue_size=10)
        self.lead_x = rospy.Publisher('leadcar/odom_x', Float64, queue_size=10)
        self.gap = rospy.Publisher('lead_dist', Float64, queue_size=10)
        self.rel_vel = rospy.Publisher('rel_vel', Float64, queue_size=10)
        self.set_speed = rospy.Publisher('acc/set_speed', Int16, queue_size=10)
        self.ego_vel = rospy.Publisher('car/state/vel_x', Float64, queue_size=10)
        self.track_pubs = [rospy.Publisher(TRACK[1:] % k, PointStamped, queue_size=10)
                           for k in range(len(self.slots))]
        self.track_sent = [-1] * len(self.slots)   # index of the last message sent per slot

        self.v_ego = None   # latest plant speed
        self.count = 0      # plant front_x messages so far
        self.step = -1      # plant steps since the replay started
        self.x = None
        self.go_wall = None
        rospy.Subscriber('car/state/vel_x', Float64, self.vel_callback)
        rospy.Subscriber('front_x', Float64, self.front_callback)

        rospy.loginfo('lead_from_bag: %s from %.2f s for %.0f s, gap0 %.1f m, v0 %.2f m/s'
                      % (self.bag, self.start, self.duration, self.gap0, self.v0))
        self.preroll_timer = rospy.Timer(rospy.Duration(self.dt), self.preroll)
        rospy.set_param('~ready', True)

    def from_plant(self, msg):
        # skip our own pre-roll stand-in for the ego
        return msg._connection_header.get('callerid') == self.plant

    def set_speed_at(self, t):
        return int(at(self.set_speeds, t)) if self.set_speeds[0] else 0

    def preroll(self, _event):
        if self.go_wall is not None:
            self.preroll_timer.shutdown()
            return
        v_lead = at(self.speeds, 0.0)
        self.ego_vel.publish(self.v0)
        self.lead_vel.publish(v_lead)
        self.gap.publish(self.gap0)
        self.rel_vel.publish(v_lead - self.v0)
        self.set_speed.publish(self.set_speed_at(0.0))

    def vel_callback(self, msg):
        if self.from_plant(msg):
            self.v_ego = msg.data

    def front_callback(self, msg):
        if not self.from_plant(msg):
            return
        self.count += 1
        if self.count % self.per_step or self.v_ego is None:
            return  # not the last message of this plant step
        self.step += 1
        t = self.step * self.dt
        v_lead = at(self.speeds, t)
        if self.step == 0:
            self.x = msg.data + self.gap0
            self.go_wall = rospy.get_time()
            rospy.loginfo('lead_from_bag: ego plant is up (front_x %.2f, v %.2f); replay starts, lead at %.2f'
                          % (msg.data, self.v_ego, self.x))
        else:
            self.x += 0.5 * (at(self.speeds, t - self.dt) + v_lead) * self.dt
        self.lead_vel.publish(v_lead)
        self.lead_x.publish(self.x)
        self.gap.publish(self.x - msg.data)
        self.rel_vel.publish(v_lead - self.v_ego)
        self.set_speed.publish(self.set_speed_at(t))
        # radar tracks (20 Hz per slot on the car, the plant's rate): each slot's
        # latest message up to t, if it is new since the last step
        for k, (times, msgs) in enumerate(self.slots):
            i = bisect.bisect_right(times, t) - 1
            if i > self.track_sent[k]:
                self.track_sent[k] = i
                self.track_pubs[k].publish(msgs[i])
        if t >= self.duration:
            rospy.loginfo('lead_from_bag: %.0f s window done (%.1f s of wall time, %d plant steps)'
                          % (self.duration, rospy.get_time() - self.go_wall, self.step))
            rospy.signal_shutdown('window done')


if __name__ == '__main__':
    rospy.init_node('lead_from_bag')
    LeadFromBag()
    rospy.spin()
