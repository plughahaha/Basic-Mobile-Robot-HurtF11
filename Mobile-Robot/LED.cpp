#include "LED.h"

LED::LED(int pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);  
}

void LED::turnOn() {
  digitalWrite(ledPin, HIGH);  
}

void LED::turnOff() {
  digitalWrite(ledPin, LOW);  
}

void LED::blink(int delayTime) {
  turnOn();
  delay(delayTime);
  turnOff();
  delay(delayTime);
}
