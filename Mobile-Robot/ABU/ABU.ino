#include "MOTOR.h"
#define led 25
#include "pio_encoder.h"

PioEncoder encoder_FR(16);
PioEncoder encoder_BL(18);
PioEncoder encoder_BR(20);
PioEncoder encoder_FL(0);
Motor motor_FL(2, 3, 4);
Motor motor_BL(6, 7, 8);
Motor motor_FR(10, 11, 12);
Motor motor_BR(13, 14, 15);

double Kp = 0, Ki = 0, Kd = 0;
double Kp_FL = 7, Ki_FL = 0, Kd_FL = 10;
double Kp_FR = 7, Ki_FR = 0, Kd_FR = 10;
double Kp_BL = 7, Ki_BL = 0.01, Kd_BL = 10;
double Kp_BR = 10, Ki_BR = 0.01, Kd_BR = 10;
double integral_FR = 0, integral_FL = 0, integral_BL = 0, integral_BR = 0;
double previous_error_FL = 0, previous_error_FR = 0, previous_error_BL = 0, previous_error_BR = 0;

int error_FL = 0;
int error_FR = 0;
int error_BL = 0;
int error_BR = 0;
int base_speed = 100;

int en_FL = 0;
int en_FR = 0;
int en_BL = 0;
int en_BR = 0;

int output_FL = 0;
int output_FR = 0;
int output_BL = 0;
int output_BR = 0;

double tick = 0;
double average_encoder = 0;
double average_delta = 0;
double delta_FL = 0;
double delta_FR = 0;
double delta_BL = 0;
double delta_BR = 0;
double cal_delta_FL = 0;
double cal_delta_FR = 0;
double cal_delta_BL = 0;
double cal_delta_BR = 0;

#include "Motorstop.h"
#include "Control_movement.h"

void setup() {
  encoder_FR.begin();
  encoder_BL.begin();
  encoder_BR.begin();
  encoder_FL.begin();
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  for (int i = 1; i < 20; i++) {
    digitalWrite(led, HIGH);
    delay(30);
    digitalWrite(led, LOW);
    delay(30);
  }
  digitalWrite(led, HIGH);

  Control_movement("Forward",3);
  motorstop();
  Control_movement("Backward",3);
  motorstop();
  Control_movement("SL",3);
  motorstop();
  Control_movement("SR",6);
  motorstop();
}

void loop() {
}
