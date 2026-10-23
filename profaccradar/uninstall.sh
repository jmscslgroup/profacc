#!/bin/bash

echo "=========================="
echo "Removing App profaccradar"


LIBPANDA_USER=$(cat /etc/libpanda.d/libpanda_usr)

# Disable the installed services:
echo " - Disabling startup scripts..."
systemctl disable profaccradar


# Here is where we remove scripts, services, etc.
# Always uninstall the robot_upstart job: it is not listed by systemctl
# once stopped, and a leftover /etc/ros/noetic/profaccradar.d/*.launch would be
# started next to the next app's launch file.
echo " - Removing scripts..."
cd
echo "Uninstalling profaccradar.service"
source /home/$LIBPANDA_USER/catkin_ws/devel/setup.bash
rosrun robot_upstart uninstall profaccradar

systemctl daemon-reload # if needed
