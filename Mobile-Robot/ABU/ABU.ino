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

double Kp = 5.0, Ki = 0.1, Kd = 10;
double integral = 0;
double previous_error = 0;
int error = 0;
int base_speed = 128;
int output = 0;
int en_FL = 0;
int en_FR = 0;
int en_BL = 0;
int en_BR = 0;

#include "Forward.h"
#include "Backward.h"

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
}

void loop() {
  Backward(40);

  // en_FR = encoder_FR.getCount();
  // Serial.print("encoder FR = ");
  // Serial.println(en_FR);
  // delay(300);
}
