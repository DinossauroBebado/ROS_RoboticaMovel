// W Movimento	linear	para	frente
// X Movimento	linear	para	trás
// A Movimento	angular	anti-horário
// D Movimento	angular	horário
// Q Movimento	linear	para	frente	com	giro	anti-horário
// Z Movimento	linear	para	trás	com	giro	anti-horário
// E Movimento	linear	para	frente	com	giro	horário
// C Movimento	linear	para	trás	com	giro	horário
// S Parado
// 1 Incrementa	a	velocidade	linear
// 2 Decrementa	a	velocidade	linear
// 3 Incremente	a	velocidade	angular
// 4 Decrementa	a	velocidade	angular
// P Fechar	o	nó

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>   
#include "kbhit.h"

using namespace std;
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_controle");
 
  ros::NodeHandle n;
 
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
 
  ros::Rate loop_rate(10);

 
  if (ros::ok())
  {
    	geometry_msgs::Twist msg;

  //entender o porque de precisar disso para rodar 
	system("rosservice call reset");

	while(1){
            if (kbhit()){

                      switch(getchar()){
                      
                      case 'w':
                            // go forward 
                            ROS_INFO("w");
                            ros::spinOnce();
                            msg.angular.z= 0;
                            msg.linear.x = 1;
                            pub.publish(msg);
                                ros::spinOnce();
                            sleep(1);
                            break;
                       case 'x':
                            //go back 
                             ROS_INFO("X");
                             ros::spinOnce();
                             msg.angular.z = 0; 
                             msg.linear.x = -1;
                            pub.publish(msg);
                                ros::spinOnce();
                            sleep(1);
                            break;
                        case 'a':
                            //go back 
                             ROS_INFO("a");
                             ros::spinOnce();
                             msg.linear.x = 0;
                             msg.angular.z = M_PI/2;
                            pub.publish(msg);
                                ros::spinOnce();
                            sleep(1);
                            break;
                        default:
                        ros::spinOnce();
          
                        msg.linear.x = 0;
                        msg.angular.z = 0 ;
                        pub.publish(msg);
                            ros::spinOnce();
                        sleep(1);
                      }
                      
 

            }		
 }
 

 
	
  }
 
  return 0;
}



