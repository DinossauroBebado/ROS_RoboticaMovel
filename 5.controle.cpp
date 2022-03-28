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
//roscore | inicia o ros 
//rosrun turtlesim turtlesim_node | roda o modulo da tartaruga 
//rosrun tutorial_ros 5.controle | inicia esse no 

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
                     ros::spinOnce();
                      switch(teclado){
                      
                      case 'w':
                            // W Movimento	linear	para	frente
                            ROS_INFO("w");
                           
                            msg.angular.z= 0;
                            msg.linear.x = vel_linear;
                            
                            
                            break;
                       case 'x':
                            // X movimento linear para trás
                             ROS_INFO("X");
                             
                             msg.angular.z = 0; 
                             msg.linear.x = -vel_linear;
                           
                           
                            break;
                        case 'a':
                            //Movimento angular anti-horário
                             ROS_INFO("a");
                             
                             msg.linear.x = 0;
                             msg.angular.z =vel_angular ;
                            
                            break;
                        case 'd':
                            //Movimento angular horário
                             ROS_INFO("d");
                            
                             msg.linear.x = 0;
                             msg.angular.z = - vel_angular;
                            
                            
                            break; 
                        case 'q':
                            //Movimento linear para frente com giro anti-horário
                             ROS_INFO("q");
                             
                             msg.linear.x = vel_linear;
                             msg.angular.z =  vel_angular;
                         
                            break;
                        case 'z':
                            //Movimento linear para trás com giro anti-horario
                             ROS_INFO("z");
                           
                             msg.linear.x = -vel_linear;
                             msg.angular.z = vel_angular;
                           
                            
                            break; 
                        case 'e':
                            //Movimento linear para frente com giro horario 
                             ROS_INFO("e");
                            
                             msg.linear.x = vel_linear;
                             msg.angular.z = - vel_angular;
                            
                            
                            break; 
                        case 'c':
                            //Movimento linear para tras com giro horario  
                             ROS_INFO("c");
                            
                             msg.linear.x = -vel_linear;
                             msg.angular.z =  - vel_angular;
                           
                            
                            break; 
                        case 's':
                            //Parado  
                             ROS_INFO("s");
                          
                             msg.linear.x = 0;
                             msg.angular.z =  0;
                           
                            break; 
                        case 'p':
                            //Fecha o Nó
                            ROS_INFO("NODE shutdown");
                            //close node s
                            ros::shutdown();
                            break;
                        case '1':
                            //incrementa a velocidade linear
                            ROS_INFO("1");
                           
                              
                             vel_linear = vel_linear +1 ;
                             msg.linear.x = vel_linear;

                            break; 
                        case '2':
                             //Decrementa  a velocidade linear 
                            ROS_INFO("2");
                           
                              
                             vel_linear = vel_linear -1 ;
                             msg.linear.x = vel_linear;

                            break;  
                        case '3':
                             //Incrementa a velocidade angular 
                            ROS_INFO("3");
                           
                              
                             vel_angular = vel_linear + M_PI/4 ;
                             msg.angular.z= vel_angular;

                            break; 
                        case '4':
                             //Decrementa a velocidade angular 
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
                      
                pub.publish(msg);
                ros::spinOnce();

            }		
 }
 

 
	
  }
 
  return 0;
}



