#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
  private:
    int ledPin;

  public:
    LED(int pin);   
    void turnOn();  
    void turnOff();  
    void blink(int delayTime);
};

#endif
