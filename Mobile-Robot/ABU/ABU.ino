#include "MOTOR.h"                                                   
#define led 25

Motor motor1(2,3,4);
Motor motor2(6,7,8);
Motor motor3(10,11,12);
Motor motor4(13,14,15);

void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  // delay(1000);
  // digitalWrite(led,LOW);
  // delay(1000);
  // digitalWrite(led,HIGH);
  // delay(1000);
  
}

void loop() {
  motor1.speed(128);
  motor2.speed(128);
  motor3.speed(128);
  motor4.speed(128);
  delay(5000);
  
  
  
  
}

// motor1.speed(255);
// delay(3000);
// motor1.stop();
// delay(3000);
// motor1.speed(-255);
// delay(3000);
// motor1.stop();
// delay(3000);
