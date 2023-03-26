#!/bin/sh
xterm  -e  " source /opt/ros/noetic/setup.bash; roscore" & 
sleep 5
xterm  -e  " roslaunch turtlebot3_gazebo turtlebot3_world.launch " &
sleep 5
xterm  -e  " roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch " &
sleep 5
xterm  -e  " roslaunch turtlebot3_slam turtlebot3_gmapping.launch " &
sleep 5
xterm  -e  " roslaunch turtlebot3_navigation turtlebot3_navigation.launch "