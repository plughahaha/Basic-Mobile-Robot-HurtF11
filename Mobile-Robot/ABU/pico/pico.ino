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

int last_x = 0;
int last_y = 0;
int position_x = 0;
int position_y = 0;


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

double current_position = 0;
double previous_time;
double current_time;
double posi;

// Volocity
int TICKS_PER_REVOLUTION = 4000;
double WHEEL_RADIUS = 0.05;
double DELTA_T = 0.01;
volatile long ticksChange_velocity = 0;
volatile long ticksPrevious_velocity = 0;
unsigned long lastTime = 0;
double previousTime_velocity;
double previousTicks_velocity;

double omega = 0 ;
double velocity = 0;
// Volocity

#include "Motorstop.h"
#include "Control_movement.h"
#include "Two_motor_FR.h"
#include "Two_motor_FL.h"
#include "Condition_XY.h"

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

  motor_FL.speed(128);
  motor_FR.speed(128);
  motor_BL.speed(128);
  motor_BR.speed(128);
  delay(3000);
  motorstop();
  delay(1000);

  // Control Check
  // Two_motor_FR("FR", 200);
  // motorstop();
  // Two_motor_FR("BL", 200);
  // motorstop();
  // Two_motor_FL("FL", 200);
  // motorstop();
  // Two_motor_FL("BR", 200);
  // motorstop();

  // Control_movement("Forward", 60);
  // motorstop();
  // Control_movement("Backward", 60);
  // motorstop();
  // Control_movement("SL", 60);
  // motorstop();
  // Control_movement("SR", 60);
  // motorstop();

  while (!Serial)
    Serial.println("Enter (x,y) for coordinates or command.");
}

void loop() {
  // Serial.print("previous time = ");
  // Serial.print(previous_time);
  // Serial.print(" , current time = ");
  // Serial.println(millis());
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("(") && input.endsWith(")")) {
      int commaIndex = input.indexOf(',');
      if (commaIndex != -1) {
        int x = input.substring(1, commaIndex).toInt();
        int y = input.substring(commaIndex + 1, input.length() - 1).toInt();
        Condition_XY(x, y);
      }
    } else if (input == "star" || input == "home") {
      Serial.println("choose star and home");
    } else {
      Serial.println("Invalid input!");
    }
  }
}

// Control_movement("Forward",1);
// motorstop();
// Control_movement("Backward",1);
// motorstop();
// Control_movement("SL",1);
// motorstop();
// Control_movement("SR",2);
// motorstop();
