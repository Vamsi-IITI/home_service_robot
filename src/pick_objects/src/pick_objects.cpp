#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal,goal1;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  // Define a position and orientation for the robot to reach
  // pickup zone
  goal.target_pose.pose.position.x = -1.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup zone location");
  ac.sendGoal(goal);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its pickup zone
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, Robot reached the pickup zone");
    ROS_INFO("Robot is waiting for 5 seconds");
    ros::Duration(5.0).sleep();
  }
  else {
    ROS_INFO("The base failed to reach the pickup zone for some reason");
  }

  // set up the frame parameters
  goal1.target_pose.header.frame_id = "map";
  goal1.target_pose.header.stamp = ros::Time::now();
  
  // Define a position and orientation for the robot to reach
  // drop off zone
  goal1.target_pose.pose.position.x = 4.5;
  goal1.target_pose.pose.position.y = 4.5;
  goal1.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off zone location to server");
  ac.sendGoal(goal1);

  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, Robot reached the drop off zone");
  else
    ROS_INFO("The base failed to reach the drop off zone for some reason");

  return 0;
}