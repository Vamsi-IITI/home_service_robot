#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch autonomous_turtlebot3 turtlebot3_world.launch " & 

sleep 5

# launch turtlebot3_slam.launch to perform slam_gmapping
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch turtlebot3_slam turtlebot3_slam.launch " &

sleep 5

# launch teleop_keyboard for manual control
xterm -e "cd ~/home_service_robot;
source devel/setup.bash;
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch" 

# save using following on command line
# rosrun map_server map_saver -f <map-location-and-name>