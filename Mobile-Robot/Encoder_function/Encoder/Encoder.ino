#include "RPi_Pico_TimerInterrupt.h"
// Default #define dt_us 1000
#define dt_us 1000
float deltaT = dt_us / 1.0e6;
RPI_PICO_Timer Timer(0);
bool TimerStatus = false;

#include "MOTOR.h"
Motor motor_FR(10, 11, 12);

#define encoder_A 17
#define encoder_B 16
#define led 25
int count_X1;
int count_X2;
int count_X4;

int ticks;
int TPR = 3900;
float rpm;
int last_count_X4;

int print;
int last_print;
int lastState_A;
int lastState_B;

void setup() {
  pinMode(encoder_A, INPUT);
  pinMode(encoder_B, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  lastState_A = digitalRead(encoder_A);
  lastState_B = digitalRead(encoder_B);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(encoder_A), Encoder_function, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_B), Encoder_function, CHANGE);
  TimerStatus = Timer.attachInterruptInterval(dt_us, TimerHandler);

  motor_FR.speed(255);
}

void loop() {
  if (last_print != print) {
    // Serial.print("count X1 = ");
    // Serial.print(count_X1);
    // Serial.print("\t\t");

    // Serial.print("count X2 = ");
    // Serial.print(count_X2);
    // Serial.print("\t\t");

    // Serial.print("count X4 = ");
    // Serial.print(count_X4);
    // Serial.println("\t\t");

    Serial.print("RPM = ");
    Serial.println(rpm);
    
    print = last_print;
  }
}

void Encoder_function() {
  // encoder X1 ----- read just Rising of X1
  // Rising
  if (lastState_A == LOW && digitalRead(encoder_A) == HIGH) {
    if (digitalRead(encoder_B) == LOW) {
      count_X1 += 1;
      count_X2 += 1;
      count_X4 += 1;
    } else {
      count_X1 -= 1;
      count_X2 -= 1;
      count_X4 -= 1;
    }
  }

  // encoder X2 ----- read Rising and Falling of X1
  // Falling
  if (lastState_A == HIGH && digitalRead(encoder_A) == LOW) {
    if (digitalRead(encoder_B) == HIGH) {
      count_X2 += 1;
      count_X4 += 1;
    } else {
      count_X2 -= 1;
      count_X4 -= 1;
    }
  }

  // encoder X4 ----- read Rising and Falling of X1 and X2
  // Rising
  if (lastState_B == LOW && digitalRead(encoder_B) == HIGH) {
    if (digitalRead(encoder_A) == HIGH) {
      count_X4 += 1;
    } else {
      count_X4 -= 1;
    }
  }
  // Falling
  if (lastState_B == HIGH && digitalRead(encoder_B) == LOW) {
    if (digitalRead(encoder_A) == LOW) {
      count_X4 += 1;
    } else {
      count_X4 -= 1;
    }
  }

  lastState_A = digitalRead(encoder_A);
  lastState_B = digitalRead(encoder_B);
  print += 1;
}

bool TimerHandler(struct repeating_timer* t) {
  (void)t;
  ticks = count_X4 - last_count_X4;
  last_count_X4 = count_X4;

  rpm = ((float)ticks / TPR) * (60 / deltaT);
  return true;
}

