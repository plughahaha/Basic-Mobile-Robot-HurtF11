#include "LED.h"

LED Led(LED_BUILTIN);  

void setup() {
  
}

void loop() {
  Led.blink(100);  
}
