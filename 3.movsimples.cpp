#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
 
using namespace std;
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_movimento_simples");
 
  ros::NodeHandle n;
 
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
 
  ros::Rate loop_rate(10);
 
  if (ros::ok())
  {
    	geometry_msgs::Twist msg;
	int i;
 
	ROS_INFO("Pressione qualquer tecla para iniciar...");
	system("rosservice call reset");
	getchar();
	ros::spinOnce();
 
	msg.linear.x = 2;
	pub.publish(msg);
    	ros::spinOnce();
	sleep(2);
 
        msg.linear.x = 0;
        pub.publish(msg);
        ros::spinOnce();
 
        ROS_WARN("Trajeto finalizado...");
  }
 
  return 0;
}
