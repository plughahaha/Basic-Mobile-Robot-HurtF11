#define encoder_A 17
#define encoder_B 16
#define led 25
int count_X1;

void setup() {
  pinMode(encoder_A, INPUT);
  pinMode(encoder_B, INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(encoder_A), Encoder_function, RISING);
}

void loop() {
}

void Encoder_function() {
  // encoder X1
  if (digitalRead(encoder_B) == LOW) {
    count_X1 += 1;
  } else {
    count_X1 -= 1;
  }
  Serial.print(count_X1);
  
}
