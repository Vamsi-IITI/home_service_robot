#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot3_gazebo turtlebot3_world.launch " & 

sleep 5

# launch gmapping_demo.launch to perform slam_gmapping
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot3_slam turtlebot3_gmapping.launch " &

sleep 5

# launch view_navigation for rviz
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot3_navigation turtlebot3_navigation.launch" &

sleep 5

# launch teleop_keyboard for manual control
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" 

# save using following on command line
# rosrun map_server map_saver -f <map-location-and-name>