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

                      char comando = getchar(); 
                      
                      if(comando=='a'){
                        ROS_INFO("A");
                        ros::spinOnce();
          
                        msg.linear.x = 2;
                        pub.publish(msg);
                            ros::spinOnce();
                        sleep(2);
                      
                              msg.linear.x = 0;
                              pub.publish(msg);
                              ros::spinOnce();
                      }
            
            }		
 }
 

 
	
  }
 
  return 0;
}



