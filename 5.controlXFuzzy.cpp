#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
using namespace std;

#include "FLIE-master/flie.h"

turtlesim::Pose feedback;

void subCallback(const turtlesim::Pose::ConstPtr& msg)
{
	feedback.x = msg->x;
	feedback.y = msg->y;
	feedback.theta = msg->theta;
	feedback.linear_velocity = msg->linear_velocity;
	feedback.angular_velocity = msg->angular_velocity; 
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_controle_X");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, subCallback);

  ros::Rate loop_rate(10);

  system("rosservice call reset");

//---------------------------
/*Deve-se definir um sistema de controle que ira conter as regras.*/
fuzzy_control fc;

/*No programa principal e necessario instanciar as variaveis para conter
todos os conjuntos fuzzy e tambem defini-los.*/

fuzzy_set cat[10];

/*Deve-se definir as variaveis linguisticas que irao conter os conjuntos fuzzy*/

linguisticvariable Error, Control;

/*Deve-se definir as regras de inferencia que irao reger o comportamento do
sistema de controle. Eh necessario instancia-los.*/

rule infrule[4];


/* Define-se os conjuntos fuzzy para a variavel linguistica Error*/

cat[0].setname("NB");
cat[0].setrange(-10,0);
cat[0].setval(-10,-10, -3, -1);

cat[1].setname("NS");
cat[1].setrange(-10,0);
cat[1].setval(-3,-1,0);

cat[2].setname("QZ");
cat[2].setrange(-10,+10);
cat[2].setval(-1,0,1);

cat[3].setname("PS");
cat[3].setrange(0,+10);
cat[3].setval(0,1,3);

cat[4].setname("PB");
cat[4].setrange(0,+10);
cat[4].setval(1, 3, 10, 10);

/*Define-se a Variavel linguistica Error*/

Error.setname("Error");

Error.includecategory(&cat[0]);

Error.includecategory(&cat[1]);

Error.includecategory(&cat[2]);

Error.includecategory(&cat[3]);

Error.includecategory(&cat[4]);

/*Define-se os conjuntos fuzzy para a variavel linguistica Control*/

cat[5].setname("NB");
cat[5].setrange(-5,0);
cat[5].setval(-5,-5,-0.5,-0.3);

cat[6].setname("NS");
cat[6].setrange(-5,0);
cat[6].setval(-0.5,-0.3,0);

cat[7].setname("QZ");
cat[7].setrange(-5,+5);
cat[7].setval(-0.3,0,0.3);

cat[8].setname("PS");
cat[8].setrange(0,+5);
cat[8].setval(0,0.3,0.5);

cat[9].setname("PB");
cat[9].setrange(0,+5);
cat[9].setval(0.3,0.5,5,5);


/*Define-se a variavel linguistica Control*/

Control.setname("Control");

Control.includecategory(&cat[5]);

Control.includecategory(&cat[6]);

Control.includecategory(&cat[7]);

Control.includecategory(&cat[8]);

Control.includecategory(&cat[9]);

/*Define-se o metodo defuzzificacao: MAXIMUM, AVERAGEOFMAX, or CENTEROFAREA/CENTROID     */
fc.set_defuzz(CENTROID);


/* Define-se o fuzzy_control pela entrada fuzzy( Error)
e saida (Control) )*/

fc.definevars(Error, Control);

/*Deve-se incluir cada regra fuzzy no fuzzy_control*/

// If Error IS Negative Big THEN Control IS Negative Big
fc.insert_rule("NB","NB");

// If Error IS Negative Small THEN Control IS Negative Small
fc.insert_rule("NS","NS");

// If Error IS Positive Big THEN Control IS Positive Big
fc.insert_rule("PB","PB");

// If Error IS Positive Small THEN Control IS Small
fc.insert_rule("PS","PS");



//---------------------------
  if (ros::ok())
  {
    geometry_msgs::Twist msg;
    float desejado, erro=99;
    float tolerance = 0.01;

    cout << "Digite a posicao\nX>>";
    cin >> desejado;

    while (abs(erro) > tolerance) {
	
	erro = desejado-feedback.x;

	msg.linear.x  = fc.make_inference(erro);

  	 ROS_INFO("X>>%f,Erro>>%f",feedback.x,erro);

    	pub.publish(msg);

    	ros::spinOnce();

    	loop_rate.sleep();

	}
        ROS_WARN("...Posicao alcancada...");

  }

  return 0;
}
