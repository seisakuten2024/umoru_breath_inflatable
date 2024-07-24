#include <ros.h>
#include <std_msgs/Int8.h>
#define ANALOG_PIN_0 0

int val0;
std_msgs::Int8 sensor_msg;
float v, p;
int P;

ros::NodeHandle nh;
ros::Publisher sensor_pub("sensor", &sensor_msg);

void setup() {
  Serial.begin(115200);
  nh.getHardware()->setBaud(57600);
  nh.advertise(sensor_pub);
  nh.initNode();
}

void loop() {
  val0 = analogRead(ANALOG_PIN_0);
  v = (val0 * 5.0) /1024.0;
  v = v - 0.18;
  p = v / (0.0012858 * 5.0);
  P = int(p);
  sensor_msg.data = P;
  Serial.println(sensor_msg.data);
  sensor_pub.publish(&sensor_msg);
  nh.spinOnce();
  delay(1000);
}