#include <ros.h>
#include <std_msgs/Int8.h>
#define ANALOG_PIN 0
#define DIGITAL_PIN 13

int P,val0;
std_msgs::Int8 sensor_msg;
float v,p;
int count = 0;

//comment in this area when you get the value of air pressure sensor through ROS
//ros::NodeHandle nh;
//ros::Publisher sensor_pub("sensor", &sensor_msg);

void setup() {
  Serial.begin(115200); //comment out this line when you get the value of air pressure sensor through ROS
  pinMode(DIGITAL_PIN,OUTPUT);
  //comment in this area when you get the value of air pressure sensor through ROS
  //nh.getHardware()->setBaud(57600);
  //nh.advertise(sensor_pub);
  //nh.initNode();
}

void loop() {
  val0 = analogRead(ANALOG_PIN);
  v = (val0 * 5.0) /1024.0;
  p = (v -0.18) / (0.0012858 * 5.0);
  P = int(p);
  Serial.println(P); //comment out this line when you get the value of air pressure sensor through ROS
  //comment in below lines when you get the value of air pressure sensor through ROS
  //sensor_msg.data = P;    
  //sensor_pub.publish(&sensor_msg);

  if (P > 3 || count == 500){
    digitalWrite(DIGITAL_PIN,LOW);
    delay(7000);
    count = 0;
  }else{
    digitalWrite(DIGITAL_PIN,HIGH);
    count++;
  }
  delay(10);
  //nh.spinOnce();
}