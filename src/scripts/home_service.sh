#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "roslaunch autonomous_turtlebot3 turtlebot3_world.launch " & 

sleep 5

# launch turtlebot3_navigation.launch to perform AMCL Localazation and do path planning using ROS DWA planner . Also launch rviz
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "roslaunch turtlebot3_navigation turtlebot3_navigation.launch " &

sleep 5

# launch virtual_object node that adds markers to rviz and pick_objects node using home_service.launch
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "roslaunch home_service home_service.launch" 