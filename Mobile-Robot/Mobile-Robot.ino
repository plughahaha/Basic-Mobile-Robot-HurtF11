#include "Motor.h"

void setup() {
  // Motor(Motor , Direction , speed , Time )
  Motor("Motor1","Forward",255,5000);
  Motor("Motor1","Backward",255,5000);

  Motor("Motor2","Forward",255,5000);
  Motor("Motor2","Backward",255,5000);
} 

void loop() {

}