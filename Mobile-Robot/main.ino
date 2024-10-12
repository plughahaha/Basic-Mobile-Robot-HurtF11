#include "LED.h"
#include "MOTOR.h"

LED Led(LED_BUILTIN);  

Motor motor1(9,2,3);
Motor motor2(10,4,5);

void setup() {
  Led.turnOn();
  delay(1000);
  Led.turnOff();
  delay(1000);
  
}

void loop() {
  motor1.speed(255);
  delay(1500);
  motor1.stop();

  motor2.speed(255);
  delay(1500);
  motor2.stop();
}
