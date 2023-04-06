# Home Service Robot
ROS packages for making a home service robot to reach multiple navigation goals

## Instructions for use :

```
git clone https://github.com/Vamsi-IITI/home_service_robot.git
```
```
cd home_service_robot
```
```
catkin_make
```
```
source devel/setup.bash
```

For gnome terminal :
```
./src/scripts/home_service.sh
```
For xterm terminal :
```
./src/xterm_scripts/home_service.sh
```

### Note :
If robot fails to perform its tasks , increasing tolerance value in virtual_object.cpp file in home_service_package will help.Or re-run the script.

### Video Demo :
https://drive.google.com/file/d/1wOyHHA9K3A9h0fboxtkdD43nQviXA9Q6/view?usp=share_link

## Brief Explanation

### Official ROS packages 
Import these packages now and install them in the src directory of your catkin workspace. https://github.com/ROBOTIS-GIT/turtlebot3.git

**turtlebot3_teleop**: With the ```keyboard_teleop.launch``` file, you can manually control a robot using keyboard commands.

**turtlebot3_navigation**: With the ```turtlebot3_navigation.launch``` file, you perform AMCL Localazation and do path planning using ROS DWA planner . Also launch a preconfigured rviz workspace. You’ll save a lot of time by launching this file, because it will automatically load the robot model, trajectories, and map for you and, perform localization and path planning.

**turtlebot3_slam**: With the ```turtlebot3_slam.launch``` file , you can perform slam_gmapping and generate map of environment

**turtlebot3_gazebo**: With the ```turtlebot3_world.launch``` you can deploy a turtlebot in a gazebo environment by linking the world file to it.

### Packages and Directories

**autonomous_turtlebot3**: This package has world file ,map files , rvizConfig file as well as modified launch files.

**maps**: Inside this directory, the map yaml file and pgm file generated from SLAM are stored.

**scripts**: Inside this directory,shell scripts for gnome terminal are stored.

**xterm_scripts**: Inside this directory,shell scripts for xterm terminal are stored.

**rvizConfig**: Inside this directory customized rviz configuration files have been stored.

**pick_objects**: This package has a node that commands your robot to drive to the pickup and drop off zones. ( ```pick_objects.cpp``` )

**add_markers**: This package has a node that model the object with a marker in rviz. ( ```add_markers.cpp``` )

**home_service**: This package has a ```virtual_object.cpp``` , modified version of ```add_marker.cpp``` and ```home_service.launch``` file which launches ```virtual_object``` node and ```pick_objects``` node

