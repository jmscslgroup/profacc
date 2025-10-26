#!/bin/bash

echo "=========================="
echo "Removing App profacc"


LIBPANDA_USER=$(cat /etc/libpanda.d/libpanda_usr)

# Disable the installed services:
echo " - Disabling startup scripts..."
systemctl disable profacc


# Here is where we remove scripts, services, etc.
echo " - Removing scripts..."
cd
if [ "x"`systemctl list-units | grep -c profacc.service` = "x1" ]; then
    echo "Uninstalling profacc.service"

    source /home/$LIBPANDA_USER/catkin_ws/devel/setup.bash
    rosrun robot_upstart uninstall profacc
fi

systemctl daemon-reload # if needed
