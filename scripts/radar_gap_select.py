#!/usr/bin/env python3
"""Choose the space gap for the controller: the radar estimate or lead_dist.

Subscribes (remap as needed):
    lead_dist            std_msgs/Float64, whole meters, 252 = no lead
    radar_dist_estimate  std_msgs/Float64, from gps2vsl leadVelProcessing.py,
                         300 = no radar point matched the lead
Publishes:
    lead_dist_radar      std_msgs/Float64, the chosen gap (m)
    lead_dist_radar_used std_msgs/Bool, true when the radar estimate was chosen

The radar estimate is used only when all of these hold; otherwise
lead_dist passes through unchanged:
    - lead_dist sees a lead (below no_lead)
    - lead_dist is at least min_radar_dist; below that, replays showed the
      estimate wandering by 1-3 m around a steady lead_dist
    - the estimate is valid (below no_estimate) and newer than max_age

Params (private): ~min_radar_dist (10.0 m), ~max_age (0.25 s),
~rate (20.0 Hz), ~no_lead (252.0 m), ~no_estimate (300.0 m)
"""
import rospy
from std_msgs.msg import Bool, Float64


class RadarGapSelect:
    def __init__(self):
        self.min_radar_dist = rospy.get_param('~min_radar_dist', 10.0)
        self.max_age = rospy.get_param('~max_age', 0.25)
        self.no_lead = rospy.get_param('~no_lead', 252.0)
        self.no_estimate = rospy.get_param('~no_estimate', 300.0)
        rate = rospy.get_param('~rate', 20.0)

        self.lead = None
        self.estimate = None
        self.estimate_time = None

        self.gap_pub = rospy.Publisher('lead_dist_radar', Float64, queue_size=10)
        self.used_pub = rospy.Publisher('lead_dist_radar_used', Bool, queue_size=10)
        rospy.Subscriber('lead_dist', Float64, self.lead_callback)
        rospy.Subscriber('radar_dist_estimate', Float64, self.estimate_callback)
        rospy.Timer(rospy.Duration(1.0 / rate), self.publish)

    def lead_callback(self, msg):
        self.lead = msg.data

    def estimate_callback(self, msg):
        self.estimate = msg.data
        self.estimate_time = rospy.get_time()

    def radar_ok(self):
        if self.estimate is None:
            return False
        fresh = rospy.get_time() - self.estimate_time <= self.max_age
        return (fresh
                and self.estimate < self.no_estimate
                and self.min_radar_dist <= self.lead < self.no_lead)

    def publish(self, _event):
        # nothing to say until lead_dist has arrived
        if self.lead is None:
            return
        use_radar = self.radar_ok()
        self.gap_pub.publish(self.estimate if use_radar else self.lead)
        self.used_pub.publish(use_radar)


if __name__ == '__main__':
    rospy.init_node('radar_gap_select')
    RadarGapSelect()
    rospy.spin()
