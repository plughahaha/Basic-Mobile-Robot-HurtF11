#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "MOTOR.h"

class Robot {
private:
    // กำหนด PIN สำหรับมอเตอร์แต่ละตัว
    Motor motor_FL = Motor(2, 3, 4); // มอเตอร์ด้านหน้า-ซ้าย
    Motor motor_FR = Motor(10, 11, 12); // มอเตอร์ด้านหน้า-ขวา
    Motor motor_BL = Motor(6, 7, 8); // มอเตอร์ด้านหลัง-ซ้าย
    Motor motor_BR = Motor(13, 14, 15); // มอเตอร์ด้านหลัง-ขวา

public:
    void F();
    void B();

    void SL();
    void SR();

    void FR();
    void FL();
    void BR();
    void BL();

    void stop();
};

#endif
