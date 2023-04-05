## Home Service Robot
ROS packages for making a home service robot to reach multiple navigation goals

### Instructions for use :

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
```
./src/scripts/home_service.sh
```
### Note :
If robot fails to perform its tasks , increasing tolerance value in virtual_object.cpp file in home_service_package will help.
