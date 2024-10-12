#include <Arduino.h>

int ledPin = 25;  // กำหนดขา LED ที่ติดตั้งบนบอร์ด Pico

void setup() {
  pinMode(ledPin, OUTPUT);  // กำหนดขา LED ให้เป็น Output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // เปิด LED
  delay(1000);                  // รอ 500 มิลลิวินาที
  digitalWrite(ledPin, LOW);   // ปิด LED
  delay(1000);                  // รอ 500 มิลลิวินาที
}
