void Forward(int distance) {

  double tick = (distance / 8) * 4000;
  double check_out = (en_FL + en_FR + en_BL + en_BR) / 4;
  if (check_out > tick) {
    motor_FR.stop();
    motor_BR.stop();
    motor_FL.stop();
    motor_BL.stop();
    return;
  }

  en_FL = encoder_FL.getCount();
  en_FR = encoder_FR.getCount();
  en_BL = encoder_BL.getCount();
  en_BR = encoder_BR.getCount();

  int left = tick - (en_FL + en_BL);
  int right = tick - (en_FR + en_BR);

  if (left > right) {
    int delta1 = left - right;
    if (delta1 < 30) {
      error = 0;
    }
    if (delta1 > 30) {
      error = 1;
    }
    if (delta1 > 100) {
      error = 2;
    }
    if (delta1 > 200) {
      error = 3;
    }
    if (delta1 > 500) {
      error = 5;
    }
    if (delta1 > 1000) {
      error = 7;
    }
  }

  if (right > left) {
    int delta2 = right - left;
    if (delta2 < 50) {
      error = 0;
    }
    if (delta2 > 50) {
      error = -1;
    }
    if (delta2 > 100) {
      error = -2;
    }
    if (delta2 > 200) {
      error = -3;
    }
    if (delta2 > 500) {
      error = -5;
    }
    if (delta2 > 1000) {
      error = -7;
    }
  }

  output = (Kp * error) + (Ki * integral) + (Kd * (error - previous_error));

  int left_output = base_speed + output;
  int right_output = base_speed - output;

  left_output = constrain(left_output, -128, 128);
  right_output = constrain(right_output, -128, 128);

  motor_FR.speed(right_output);
  motor_BR.speed(right_output);
  motor_FL.speed(left_output);
  motor_BL.speed(left_output);

  integral += error;
  previous_error = error;

  // Serial.print("tick = ");
  // Serial.print(tick);
  // Serial.print("\t\t");

  // Serial.print("now = ");
  // Serial.print(check_out);
  // Serial.print("\t\t");

  // Serial.print("delta = ");
  // Serial.print(right - left);
  // Serial.print("\t\t");

  // Serial.print("ERROR = ");
  // Serial.print(error);
  // Serial.print("\t\t");

  // Serial.print("encoder FL = ");
  // Serial.print(en_FL);
  // Serial.print("\t\t");

  // Serial.print("encoder BL = ");
  // Serial.print(en_BL);
  // Serial.print("\t\t");

  // Serial.print("result left = ");
  // Serial.print(left);
  // Serial.print("\t\t");

  // Serial.print("encoder FR = ");
  // Serial.print(en_FR);
  // Serial.print("\t\t");

  // Serial.print("encoder BR = ");
  // Serial.print(en_BR);
  // Serial.print("\t\t");

  // Serial.print("result right = ");
  // Serial.print(right);
  // Serial.print("\t\t");

  // Serial.print("motor_left = ");
  // Serial.print(left_output);
  // Serial.print("\t\t");

  // Serial.print("motor_right = ");
  // Serial.print(right_output);
  // Serial.print("\t\t");

  // Serial.print("\n");
}