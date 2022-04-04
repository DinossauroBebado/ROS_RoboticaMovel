#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>

using namespace std;

turtlesim::Pose feedback;

void subCallback(const turtlesim::Pose::ConstPtr& msg)
{
	feedback.x = msg->x;
	feedback.y = msg->y;
	feedback.theta = msg->theta;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_PID");
  ros:: Time last_time,actual_time;

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, subCallback);

  ros::Rate loop_rate(10);

  if (ros::ok())
  { system("rosservice call reset");
    // Define variables
    geometry_msgs::Twist msg;
    double posdesejada[2], oridesejada ; 
    
    double errorP = 99 , errorSumP ,dErrorP ,lastErrorP;
    double errorO = 99 , errorSumO ,dErrorO ,lastErrorO;

    //indices do PID
    double kpP = 2 ;
    double kiP = 0;
    double kdP = 0.5;

    double kpO = 5 ;
    double kiO = 0;
    double kdO = 0.2;

    //tolerancias 
    double tolerancia_dist = 0.05;
    double tolerancia_ang = 0.005 ; 

    


    // get info 

    cout << "Digite a posicao\nX>>";
    cin >> posdesejada[0];

    cout << "Y>>";
    cin >> posdesejada[1];

     

    
    ros::spinOnce();


    
  while(abs(errorP)> tolerancia_dist || abs(errorO) > tolerancia_ang){
        last_time	=	actual_time;
        actual_time	=	ros::Time::now();
        double	dt	=	(actual_time	- last_time).toSec();



        errorP =  sqrt(pow(posdesejada[0]-feedback.x,2)+pow(posdesejada[1]-feedback.y,2)); //erro proporcional 
        
        oridesejada = atan2(posdesejada[1]-feedback.y,posdesejada[0]-feedback.x); 
        errorO= oridesejada-feedback.theta;
        ROS_WARN("Erro proporcional>>%f\n",errorP);

        errorSumP += (errorP*dt) ; // erro integral 
        errorSumO += (errorO*dt) ;
        ROS_WARN("Erro integral>>%f\n",errorSumP);

        dErrorP = (errorP - lastErrorP)/dt; // erro diferencial 
        dErrorO = (errorO - lastErrorO)/dt; 
        ROS_WARN("Erro diferencial>>%f\n",dErrorP);
      

        double outputP = kpP*errorP + kiP*(errorSumP) + kdP*dErrorP ; 
        double outputO = kpO*errorO + kiO*(errorSumO) + kdO*dErrorO ; 

        //escreve a msg 

        ROS_WARN("angulo>>%f\n",outputO);
        ROS_WARN("Posicao>>%f\n",outputP);

        msg.linear.x = outputP ; 
        msg.angular.z =  outputO ;

        
        lastErrorP = errorP ; 
        lastErrorO = errorO ; 

        pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
  }
   msg.linear.x = 0 ; 
   msg.angular.z = 0; 
   pub.publish(msg);
   ros::spinOnce();
   loop_rate.sleep();
  
  } 
  return 0;
}
