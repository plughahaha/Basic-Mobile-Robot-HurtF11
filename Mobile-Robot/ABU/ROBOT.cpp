#include "ROBOT.h"

Robot::Robot()
    : motor_FL(), motor_BL(), motor_FR(), motor_BR() {
}

void Robot::begin() {
    motor_FL.begin(2, 3, 4); 
    motor_BL.begin(6, 7, 8); 
    motor_FR.begin(10, 11, 12); 
    motor_BR.begin(13, 14, 15); 
}

void Robot::F() {
    motor_FL.speed(255);
    motor_FR.speed(255);
    motor_BL.speed(255);
    motor_BR.speed(255);
}

