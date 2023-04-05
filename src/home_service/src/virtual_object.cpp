#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <visualization_msgs/Marker.h>

// global variable K for tracking the state of the robot
int K = 0 ;
// global variables X,Y and Z for tracking the position of the robot
float X,Y,Z;
// global variable for tracking the velocity and angular velocity of the robot
float velX, velY, velZ , angVelZ;
// tolerance to account for uncertainities in the robot's position and velocity
float tol = 0.8;
float velTol = 0.001;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){

	// ROS_INFO("Seq: [%d]", msg->header.seq);
	// ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y,msg->pose.pose.position.z);
	// ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	// ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
    X = msg->pose.pose.position.x;
    Y = msg->pose.pose.position.y;
    Z = msg->pose.pose.position.z;
    velX = msg->twist.twist.linear.x;
    velY = msg->twist.twist.linear.y;
    velZ = msg->twist.twist.linear.z;
    angVelZ = msg->twist.twist.angular.z;
    // ROS_INFO("X = %f, Y = %f, Z = %f",X,Y,Z);

}

int main(int argc, char **argv){
	
	ros::init(argc, argv, "virtual_object");
	ros::NodeHandle n;

    ros::Rate r(1);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    ros::Subscriber sub = n.subscribe("odom",1000, odomCallback);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "virtual_object";
    marker.id = 0;

    // Set the marker type. This is CUBE
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the position of the marker.
    marker.pose.position.x = -1;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;

    // Set the orientation of the marker. 
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 0.3 x 0.3 x 0.3 here means 0.3 m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while(ros::ok()){

        // ROS_INFO("K = %d. Now going in code",K);
        // ROS_INFO("X = %f, Y = %f, Z = %f",X,Y,Z);
        if ( abs(X+1)<tol && abs(Y)<tol && abs(Z)<tol && abs(velX)<velTol && abs(velY)<velTol && abs(velZ)<velTol && abs(angVelZ)<velTol)
        {
            ROS_INFO_ONCE("Robot at pickup zone");
            ROS_INFO_ONCE("Virtual object picked up by robot");
            K = 1;
            marker.color.r = 0.0f;
            marker.color.a = 0.0;
            // Hide the marker . 
            marker_pub.publish(marker); 
        }

        if ( abs(X-4.5)<tol && abs(Y-4.5)<tol && abs(Z)<tol && abs(velX)<velTol && abs(velY)<velTol && abs(velZ)<velTol && abs(angVelZ)<velTol)
        {   
            ROS_INFO_ONCE("Robot at dropoff zone");
            ROS_INFO_ONCE("Virtual object delivered by robot");
            K = 2;
            marker.pose.position.x = 4.5;
            marker.pose.position.y = 4.5;
            marker.pose.position.z = 0;
            marker.color.r = 1.0f;
            marker.color.a = 1.0;
            // Publish the marker at dropoff zone. 
            marker_pub.publish(marker); 
        }

        if (K == 1 && abs(X+1)>0.4 && abs(Y)>0.4 )
        {
        ROS_INFO_ONCE("Robot headed to dropoff zone");
        marker.color.r = 0.0f;
        marker.color.a = 0.0;
        // Hide the marker . 
        marker_pub.publish(marker); 
        ROS_INFO_ONCE("Virtual object is being carried by robot");
        }

        if (K == 0){
            ROS_INFO_ONCE("Robot headed to pickup zone");
            // Publish the marker at pickup zone.
            marker.pose.position.x = -1;
            marker.pose.position.y = 0;
            marker.pose.position.z = 0;
            marker.color.r = 1.0f;
            marker_pub.publish(marker);
            ROS_INFO_ONCE("Marker / Virtual object at pickup zone");
        }

        // ROS_INFO("K = %d . Now loop",K);
        ros::spinOnce();                              // if we don't have this, the callback function will not be called and the values of X,Y,Z will not be updated
    }
    ros::spin();
	return 0;
}