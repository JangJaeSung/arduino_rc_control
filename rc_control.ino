#include <stdio.h>
#include <Servo.h>
#include <math.h>

#include <ros.h>

#include <geometry_msgs/Twist.h>


//#define DEBUG
#define pin_throttle 10 // set pin number 8 of arduino mega as rc_throttle pin 
#define pin_steer 9 // set pin number 7 of arduino mega as rc_steer pin
#define LED 13
#define ZERO_STEER 1450
#define ZERO_SPEED 1500

Servo steer;
Servo throttle;

int steer_val = ZERO_STEER;
int throttle_val = ZERO_SPEED;
int lane_steer_val_old, lane_steer_val_new = ZERO_STEER;
int lane_throttle_val = ZERO_SPEED;

float tx_steer;
float tx_throttle;



void rosTwistCallback(const geometry_msgs::Twist& twist_msg){
  tx_throttle = twist_msg.linear.x;
  tx_steer = twist_msg.angular.z;


  throttle.writeMicroseconds(throttle_val);
  steer.writeMicroseconds(steer_val);

  /*
  Serial.print(twist_msg.angular.z);
  Serial.print(",");
  Serial.println(twist_msg.linear.x);
  */
}

ros::NodeHandle nh;


ros::Subscriber<geometry_msgs::Twist> sub_twist("twist_msg", &rosTwistCallback);





void setup() {
  nh.initNode();
  nh.subscribe(sub_twist);

  Serial.begin(57600);

  steer.attach(pin_steer);
  throttle.attach(pin_throttle);

  steer.writeMicroseconds(1600);
  throttle.writeMicroseconds(1600);
  
}

void loop() {
  /*
  if(Serial.available()){
//    digitalWrite(LED, HIGH);
    lane_steer_val_old = lane_steer_val_new;
    lane_steer_val_new = tx_steer;
    lane_throttle_val = tx_throttle;
    Serial.read();

  }
  
  else{
    digitalWrite(LED, LOW);
     delay(1000);
  }
  */

  
  //if the diffrence between the pervious and persent steering values is less than 5000, the (lane)vision will control rc_car or the rplidar will control it.
  //if you want to change the Criteria then, change the value(now the Criteria is 5000). 
 // if( abs(lane_steer_val_new - lane_steer_val_old) < 5000){
    // use vision(lane) control
    
  steer_val = tx_steer;
  throttle_val = tx_throttle;
 
  /*
  else{
    //do lidar control   
    lidar_control();
  }
  */
  


  nh.spinOnce();
  delay(5);
/*
  Serial.print(tx_steer);
  Serial.print(",");
  Serial.println(tx_throttle);
*/
}
