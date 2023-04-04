#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "roslaunch autonomous_turtlebot3 turtlebot3_world.launch " & 

sleep 5

# launch turtlebot3_slam.launch to perform slam_gmapping
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "roslaunch turtlebot3_navigation turtlebot3_navigation.launch " &

sleep 5

# launch pick objects node
gnome-terminal -- bash -c "source ~/home_service_robot/devel/setup.bash";
gnome-terminal -- bash -c "rosrun pick_objects pick_objects"