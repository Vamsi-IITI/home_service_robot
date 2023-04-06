#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch autonomous_turtlebot3 turtlebot3_world.launch " & 

sleep 5

# launch turtlebot3_navigation.launch to perform AMCL Localazation and do path planning using ROS DWA planner . Also launch rviz
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch turtlebot3_navigation turtlebot3_navigation.launch " &

sleep 5

# launch virtual_object node that adds markers to rviz and pick_objects node using home_service.launch
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch home_service home_service.launch" 