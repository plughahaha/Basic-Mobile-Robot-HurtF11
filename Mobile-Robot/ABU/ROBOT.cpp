#include "ROBOT.h"

// normal
void Robot::F() {
  motor_FL.speed(128);  // เรียกใช้ฟังก์ชัน speed ของ Motor
  motor_FR.speed(128);
  motor_BL.speed(128);
  motor_BR.speed(128);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::B() {
  motor_FL.speed(-128);
  motor_FR.speed(-128);
  motor_BL.speed(-128);
  motor_BR.speed(-128);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}
// slide
void Robot::SL() {
  motor_FL.speed(-128);
  motor_FR.speed(128);
  motor_BL.speed(128);
  motor_BR.speed(-128);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::SR() {
  motor_FL.speed(128);
  motor_FR.speed(-128);
  motor_BL.speed(-128);
  motor_BR.speed(128);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}
// out
void Robot::FR() {
  motor_FL.speed(128);
  motor_FR.speed(0);
  motor_BL.speed(0);
  motor_BR.speed(128);
  delay(7000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::FL() {
  motor_FL.speed(0);
  motor_FR.speed(128);
  motor_BL.speed(128);
  motor_BR.speed(0);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::BR() {
  motor_FL.speed(0);
  motor_FR.speed(-128);
  motor_BL.speed(-128);
  motor_BR.speed(0);
  delay(1000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::BL() {
  motor_FL.speed(-128);
  motor_FR.speed(0);
  motor_BL.speed(0);
  motor_BR.speed(-128);
  delay(7000);
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}

void Robot::stop() {
  motor_FL.stop();
  motor_FR.stop();
  motor_BL.stop();
  motor_BR.stop();
}
