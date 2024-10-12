

int ledPin = 25;  // กำหนดขา LED ที่ติดตั้งบนบอร์ด Pico

void setup() {
  pinMode(ledPin, OUTPUT);  // กำหนดขา LED ให้เป็น Output
}

void loop() {
  digitalWrite(ledPin, HIGH);  // เปิด LED
  delay(100);                  // รอ 100 มิลลิวินาที
  digitalWrite(ledPin, LOW);   // ปิด LED
  delay(100);                  // รอ 100 มิลลิวินาที
}
