#include "MOTOR.h"
#define led 25
#include "pio_encoder.h"
#include "ROBOT.h"  
// #include <Wire.h> 
// #include <MPU6050.h> 

PioEncoder encA(16);
PioEncoder encB(18);
PioEncoder encC(20);
PioEncoder encD(0);

Motor motor_FL(2, 3, 4);
Motor motor_BL(6, 7, 8);
Motor motor_FR(10, 11, 12);
Motor motor_BR(13, 14, 15);
  
void setup() {
  encA.begin();
  encB.begin();
  encC.begin();
  encD.begin();
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  for (int i = 1; i < 20; i++) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  }
  digitalWrite(led, HIGH);

  while (encB.getCount() < 20000 or encB.getCount() > 20000){
  motor_FL.speed(128);
  motor_FR.speed(-128);
  motor_BL.speed(-128);
  motor_BR.speed(128);
  Serial.print(encA.getCount());
  Serial.print("\n");
  }
  motor_FL.stop();
  motor_FR.stop();
  motor_BR.stop();
  motor_BL.stop();
}

void loop() {
  Serial.print(encA.getCount());
  Serial.print("\t\t");

  Serial.print(encB.getCount());
  Serial.print("\t\t");
  
  Serial.print(encC.getCount());
  Serial.print("\t\t");

  Serial.print(encD.getCount());
  Serial.print("\n");

  delay(10);

}

