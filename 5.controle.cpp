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

//rosrun tutorial_ros 5.controle

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

    int vel_linear = 1 ; 
    float vel_angular = M_PI/2;

   

	while(1){
    
            if (kbhit()){
                 char teclado = getchar();

                      switch(teclado){
                      
                      case 'w':
                            // go forward 
                            ROS_INFO("w");
                            ros::spinOnce();
                            msg.angular.z= 0;
                            msg.linear.x = vel_linear;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break;
                       case 'x':
                            //go back 
                             ROS_INFO("X");
                             ros::spinOnce();
                             msg.angular.z = 0; 
                             msg.linear.x = -vel_linear;
                            pub.publish(msg);
                                ros::spinOnce();
                           
                            break;
                        case 'a':
                            //go back 
                             ROS_INFO("a");
                             ros::spinOnce();
                             msg.linear.x = 0;
                             msg.angular.z =vel_angular ;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break;
                        case 'd':
                            //go back 
                             ROS_INFO("d");
                             ros::spinOnce();
                             msg.linear.x = 0;
                             msg.angular.z = - vel_angular;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break; 
                        case 'q':
                            //go back 
                             ROS_INFO("q");
                             ros::spinOnce();
                             msg.linear.x = vel_linear;
                             msg.angular.z =  vel_angular;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break;
                        case 'z':
                            //go back 
                             ROS_INFO("z");
                             ros::spinOnce();
                             msg.linear.x = -vel_linear;
                             msg.angular.z = vel_angular;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break; 
                        case 'e':
                            //go back 
                             ROS_INFO("e");
                             ros::spinOnce();
                             msg.linear.x = vel_linear;
                             msg.angular.z = - vel_angular;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break; 
                        case 'c':
                            //go back 
                             ROS_INFO("c");
                             ros::spinOnce();
                             msg.linear.x = -vel_linear;
                             msg.angular.z =  - vel_angular;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break; 
                        case 's':
                            //go back 
                             ROS_INFO("s");
                             ros::spinOnce();
                             msg.linear.x = 0;
                             msg.angular.z =  0;
                            pub.publish(msg);
                                ros::spinOnce();
                            
                            break; 
                        case 'p':
                            ROS_INFO("NODE shutdown");
                            //close node s
                            ros::shutdown();
                            break;
                        case '1':
                             
                            ROS_INFO("1");
                           
                              
                             vel_linear = vel_linear +1 ;
                             msg.linear.x = vel_linear;

                            break; 
                        case '2':
                             
                            ROS_INFO("2");
                           
                              
                             vel_linear = vel_linear -1 ;
                             msg.linear.x = vel_linear;

                            break;  
                        case '3':
                             
                            ROS_INFO("3");
                           
                              
                             vel_angular = vel_linear + M_PI/4 ;
                             msg.angular.z= vel_angular;

                            break; 
                        case '4':
                             
                            ROS_INFO("4");
                           
                              
                             vel_angular = vel_linear - M_PI/4 ;
                             msg.angular.z= vel_angular;

                            break; 
                        default:

                        ros::spinOnce();
          
                        msg.linear.x = 0;
                        msg.angular.z = 0 ;
                        pub.publish(msg);
                            ros::spinOnce();
                        
                      }
                      
 

            }		
 }
 

 
	
  }
 
  return 0;
}



