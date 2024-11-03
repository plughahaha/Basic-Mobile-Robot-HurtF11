#include "MOTOR.h"
#define led 25
#include "pio_encoder.h"

// Tool BOX
float tick = 0;
float position_x = 0;
float position_y = 0;
int base_speed = 128;

PioEncoder encoder_FR(16);
PioEncoder encoder_BL(18);
PioEncoder encoder_BR(20);
PioEncoder encoder_FL(0);
Motor motor_FL(2, 3, 4);
Motor motor_BL(6, 7, 8);
Motor motor_FR(10, 11, 12);
Motor motor_BR(13, 14, 15);

float last_x = 0;
float last_y = 0;

float Kp = 0, Ki = 0, Kd = 0;
float Kp_FL = 7, Ki_FL = 0, Kd_FL = 10;
float Kp_FR = 7, Ki_FR = 0, Kd_FR = 10;
float Kp_BL = 7, Ki_BL = 0.01, Kd_BL = 10;
float Kp_BR = 10, Ki_BR = 0.01, Kd_BR = 10;
float integral_FR = 0, integral_FL = 0, integral_BL = 0, integral_BR = 0;
float previous_error_FL = 0, previous_error_FR = 0, previous_error_BL = 0, previous_error_BR = 0;

int error_FL = 0;
int error_FR = 0;
int error_BL = 0;
int error_BR = 0;


float en_FL = 0;
float en_FR = 0;
float en_BL = 0;
float en_BR = 0;

int output_FL = 0;
int output_FR = 0;
int output_BL = 0;
int output_BR = 0;

float average_encoder = 0;
float average_delta = 0;
float delta_FL = 0;
float delta_FR = 0;
float delta_BL = 0;
float delta_BR = 0;
float cal_delta_FL = 0;
float cal_delta_FR = 0;
float cal_delta_BL = 0;
float cal_delta_BR = 0;

float current_position = 0;
float previous_time;
float current_time;

// Volocity
int TICKS_PER_REVOLUTION = 4000;
float WHEEL_RADIUS = 0.05;
float DELTA_T = 0.01;
volatile long ticksChange_velocity = 0;
volatile long ticksPrevious_velocity = 0;
unsigned long lastTime = 0;
float previousTime_velocity;
float previousTicks_velocity;

float omega = 0;
float velocity = 0;
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

  // Condition_XY(0, 0.9);
  // Condition_XY(0, 1.4);
  // Condition_XY(0, 2.35);
  
  // Control_movement("Forward", 2.5);
  // motorstop();

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
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("(") && input.endsWith(")")) {
      int commaIndex = input.indexOf(',');
      if (commaIndex != -1) {
        float x = input.substring(1, commaIndex).toFloat(); // เปลี่ยนเป็น toFloat()
        float y = input.substring(commaIndex + 1, input.length() - 1).toFloat(); // เปลี่ยนเป็น toFloat()
        Condition_XY(x, y); // ฟังก์ชันของฉันต้องการ input เป็น float 
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
