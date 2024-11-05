#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#define SENSOR_PIN 0
#define SV_PUMP_PIN 12
#define SV_EXHAUST_PIN 13

int P,val0;
std_msgs::Int8 sensor_msg;
std_msgs::Bool touch_msg;
float v,p;
int count = 0;
int state;
bool add_air_executed = false;

void demo_status_cb(const std_msgs::Bool &msg){
  if(!msg.data){
    state = 0; //待機状態に戻る
  }
}

//comment in this area when you get the value of air pressure sensor through ROS
ros::NodeHandle nh;
ros::Publisher sensor_pub("sensor", &sensor_msg);
ros::Publisher touch_pub("inflatable_touch", &touch_msg);
ros::Subscriber<std_msgs::Bool> demo_status_sub("/demo_status", &demo_status_cb);

void add_air() {
  digitalWrite(SV_PUMP_PIN,HIGH);
  digitalWrite(SV_EXHAUST_PIN,LOW);
  //digitalWrite(SV_EXHAUST_PIN,HIGH);
  }

void keep_pressure() {
  digitalWrite(SV_PUMP_PIN,LOW);
  digitalWrite(SV_EXHAUST_PIN,LOW);
  //digitalWrite(SV_EXHAUST_PIN,HIGH);
  }

void remove_air() {
  digitalWrite(SV_PUMP_PIN,LOW);
  digitalWrite(SV_EXHAUST_PIN,HIGH);
  //digitalWrite(SV_EXHAUST_PIN,LOW);
  }

void setup() {
  pinMode(SV_PUMP_PIN,OUTPUT);
  pinMode(SV_EXHAUST_PIN,OUTPUT);
  pinMode(SENSOR_PIN,INPUT);

  nh.getHardware()->setBaud(57600);
  Serial.begin(115200); 
  nh.initNode();
  while(!nh.connected())
  {
    nh.spinOnce();
    delay(10);
  }
  nh.advertise(sensor_pub);
  nh.advertise(touch_pub);
  nh.subscribe(demo_status_sub);
  state = 0;
}

void loop() {
  val0 = analogRead(SENSOR_PIN);
  v = (val0 * 5.0) /1024.0;
  p = (v -0.18) / (0.0012858 * 5.0);
  P = int(p);
  Serial.println(P); //comment out this line when you get the value of air pressure sensor through ROS
  //comment in below lines when you get the value of air pressure sensor through ROS
  sensor_msg.data = P;
  sensor_pub.publish(&sensor_msg);

  if(state==0) {
    if (P<=1){
      add_air();
    }else if (P>1 && P<=3){
      keep_pressure();
    }else {
      state = 1;
      count = 0;
      //publish
      touch_msg.data = true;
      touch_pub.publish(&touch_msg);
    }
  }else if(state==1) {
    count++;
    if (!add_air_executed) {  
      add_air();
      if (P > 3) {  
        remove_air();
        add_air_executed = true;
        count = 0;
      } else if (count >= 500) {  
        remove_air();
        add_air_executed = true;
        count = 0;
      }
    } else {  
      remove_air();
      if (P < 1) {  
        add_air();
        add_air_executed = false;
        count = 0;
      } else if (count >= 1000) {  
        add_air_executed = false;
        count = 0;
      }
    }
  }

  delay(10);
  nh.spinOnce();
}