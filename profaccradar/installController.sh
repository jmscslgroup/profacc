#!/bin/bash
# Author: Matt Nice,Matt Bunting

LAUNCH_FILE=profaccradar.launch

echo "----------------------------"
if [[ $EUID == 0 ]];
  then echo "Do NOT run this script as root"
  exit
fi

source ~/.bashrc

pushd ~/catkin_ws
source devel/setup.sh

# rosrun robot_upstart install can_to_ros/launch/${LAUNCH_FILE} --user root
rosrun robot_upstart install profacc/launch/${LAUNCH_FILE} --job profaccradar --user root

echo "Enabling can_to_ros startup script"
sudo systemctl daemon-reload
sudo systemctl enable profaccradar
popd

echo "----------------------------"
