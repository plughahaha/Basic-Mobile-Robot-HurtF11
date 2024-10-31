#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "MOTOR.h"

class Robot {
private:
  Motor motor_FL;
  Motor motor_BL;
  Motor motor_FR;
  Motor motor_BR;

public:
  Robot();
  void begin();
  void F();
  void B();
  
  void SL();
  void SR();

  void FR();
  void FL();
  void BL();
  void BR();
};

#endif