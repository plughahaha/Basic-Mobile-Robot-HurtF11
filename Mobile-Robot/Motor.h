#define IN1 2
#define IN2 3
#define ENA 9
#define IN3 4
#define IN4 5
#define ENB 10

void Motor(String Motor, String Direction, int speed, int Time)
{

  if (Motor == "Motor1")
  {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);

    if (Direction == "Forward")
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    if (Direction == "Backward")
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    analogWrite(ENA, speed);
    delay(Time);
    analogWrite(ENA, 0);
  }
  else if (Motor == "Motor2")
  {
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
    if (Direction == "Forward")
    {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if (Direction == "Backward")
    {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    analogWrite(ENB, speed);
    delay(Time);
    analogWrite(ENB, 0);
  }
}

void stopMotor(int motorNum)
{
  if (motorNum == 1)
  {
    analogWrite(ENA, 0);
  }
  else if (motorNum == 2)
  {
    analogWrite(ENB, 0);
  }
}