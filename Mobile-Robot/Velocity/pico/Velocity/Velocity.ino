#include "RPi_Pico_TimerInterrupt.h"
// Default #define dt_us 1000
#define dt_us 1000
float deltaT = dt_us / 1.0e6;
RPI_PICO_Timer Timer(0);
bool TimerStatus = false;

#include "MOTOR.h"
Motor motor_FR(10, 11, 12);

#include "pio_encoder.h"
PioEncoder enc_FR(16);


int ticks;
int TPR = 3900;
float rpm;
int last_count_X4;

int print;
int last_print;

void setup() {
  enc_FR.begin();
  Serial.begin(9600);
  TimerStatus = Timer.attachInterruptInterval(dt_us, TimerHandler);
  motor_FR.speed(255);
}

void loop() {
  if (last_print != print) {
    Serial.println(rpm);
    print = last_print;
  }
}

bool TimerHandler(struct repeating_timer* t) {
  (void)t;
  ticks = enc_FR.getCount();
  rpm = ((float)ticks / TPR) * (60 / deltaT);
  enc_FR.reset();
  print += 1;
  return true;
}

