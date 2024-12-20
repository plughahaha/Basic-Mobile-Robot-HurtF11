
void Two_motor_FL(String direction, float distance) {  
  encoder_FR.reset();
  encoder_BL.reset();
  average_encoder = 0;
  average_delta = 0;
  en_FL = 0;
  en_FL = 0;
  en_BR = 0;
  en_BR = 0;
  integral_FL = 0;
  integral_FL = 0;
  integral_BR = 0;
  integral_BR = 0;
  previous_error_FL = 0;
  previous_error_FL = 0;
  previous_error_BR = 0;
  previous_error_BR = 0;
  error_FL = 0;
  error_FL = 0;
  error_BR = 0;
  error_BR = 0;
  output_FL = 0;
  output_FL = 0;
  output_BR = 0;
  output_BR = 0;
  delta_FL = 0;
  delta_FL = 0;
  delta_BR = 0;
  delta_BR = 0;
  cal_delta_FL = 0;
  cal_delta_FL = 0;
  cal_delta_BR = 0;
  cal_delta_BR = 0;
  //  douBRe tick = (distance / 8) * 3700;
  tick = (distance * (370)) * 100;
  average_encoder = 0;
  while (average_encoder < tick) {
    en_FR = encoder_FR.getCount();
    en_BL = encoder_BL.getCount();
    average_encoder = (abs(en_FR) + abs(en_BL)) / 2;

    if (key_overencoder == 0) {
      en_FL -= over_encoder_FL;
      en_FR -= over_encoder_FR;
      en_BL -= over_encoder_BL;
      en_BR -= over_encoder_BR;
      key_overencoder = 1 ;
    }

    delta_FR = tick - abs(en_FR);
    delta_BL = tick - abs(en_BL);

    average_delta = (abs(delta_FR) + abs(delta_BL)) / 2;

    if (delta_FR > average_delta) {
      cal_delta_FR = delta_FR - average_delta;
      if (cal_delta_FR < Error_Phase_1) {
        error_FR = 0;
      }
      if (cal_delta_FR > Error_Phase_1) {
        error_FR = 1;
      }
      if (cal_delta_FR > Error_Phase_2) {
        error_FR = 3;
      }
      if (cal_delta_FR > 200) {
        error_FR = 4;
      }
      if (cal_delta_FR > 500) {
        error_FR = 5;
      }
      if (cal_delta_FR > 1000) {
        error_FR = 7;
      }
    }

    if (delta_FR < average_delta) {
      cal_delta_FR = average_delta - delta_FR;
      if (cal_delta_FR < Error_Phase_1) {
        error_FR = 0;
      }
      if (cal_delta_FR > Error_Phase_1) {
        error_FR = -1;
      }
      if (cal_delta_FR > Error_Phase_2) {
        error_FR = -3;
      }
      if (cal_delta_FR > 200) {
        error_FR = -4;
      }
      if (cal_delta_FR > 500) {
        error_FR = -5;
      }
      if (cal_delta_FR > 1000) {
        error_FR = -7;
      }
    }

    // Cal delta for BL
    if (delta_BL > average_delta) {
      cal_delta_BL = delta_BL - average_delta;
      if (cal_delta_BL < Error_Phase_1) {
        error_BL = 0;
      }
      if (cal_delta_BL > Error_Phase_1) {
        error_BL = 1;
      }
      if (cal_delta_BL > Error_Phase_2) {
        error_BL = 2;
      }
      if (cal_delta_BL > 200) {
        error_BL = 3;
      }
      if (cal_delta_BL > 500) {
        error_BL = 5;
      }
      if (cal_delta_BL > 1000) {
        error_BL = 7;
      }
    }

    if (delta_BL < average_delta) {
      cal_delta_BL = average_delta - delta_BL;
      if (cal_delta_BL < Error_Phase_1) {
        error_BL = 0;
      }
      if (cal_delta_BL > Error_Phase_1) {
        error_BL = -1;
      }
      if (cal_delta_BL > Error_Phase_2) {
        error_BL = -2;
      }
      if (cal_delta_BL > 200) {
        error_BL = -3;
      }
      if (cal_delta_BL > 500) {
        error_BL = -5;
      }
      if (cal_delta_BL > 1000) {
        error_BL = -7;
      }
    }

    output_FR = (Kp_FR * error_FR) + (Ki_FR * integral_FR) + (Kd_FR * (error_FR - previous_error_FR));
    output_FR = constrain(output_FR, -255, 255);
    output_BL = (Kp_BL * error_BL) + (Ki_BL * integral_BL) + (Kd_BL * (error_BL - previous_error_BL));
    output_BL = constrain(output_BL, -255, 255);

    if (direction == "FL") {
      motor_FR.speed((base_speed + output_FR) * 1);
      motor_BL.speed((base_speed + output_BL) * 1);
    } else if (direction == "BR") {
      motor_FR.speed((base_speed + output_FR) * -1);
      motor_BL.speed((base_speed + output_BL) * -1);
    }

    integral_FR += error_FR;
    previous_error_FR = error_FR;
    integral_BL += error_BL;
    previous_error_BL = error_BL;

    // Velocity -----------------------------------------------------------------------
    if ((millis()) - previousTime_velocity >= DELTA_T * 1000) {
      ticksChange_velocity = average_encoder - previousTicks_velocity;
      omega = (ticksChange_velocity / (float)TICKS_PER_REVOLUTION) * 2 * PI / DELTA_T;
      velocity = omega * WHEEL_RADIUS;
      previousTime_velocity = millis();
      previousTicks_velocity = average_encoder;
    }
    // Velocity -----------------------------------------------------------------------

    // ----------------------------------------------------------------------------------------------------------------------------------
    if (direction == "FL") {
      Serial.print("Current Position (X,Y) = (");
      Serial.print((position_x - int(average_encoder / 370)) / 100);
      Serial.print(" m, ");
      Serial.print((position_y + int(average_encoder / 370)) / 100);
      Serial.print(" m)");
      Serial.print("          ");
    } else if (direction == "BR") {
      Serial.print("Current Position (X,Y) = (");
      Serial.print((position_x + int(average_encoder / 370)) / 100);
      Serial.print(" m, ");
      Serial.print((position_y - int(average_encoder / 370)) / 100);
      Serial.print(" m)");
      Serial.print("          ");
    }

    Serial.print("Velocity = ");
    Serial.print(velocity);
    Serial.print(" m/s");
    Serial.print("          ");

    // ----------------------------------------------------------------------------------------------------------------------------------

    // Serial.print("tick = ");
    // Serial.print(tick);
    // Serial.print("          ");

    // Serial.print("average_encoder = ");
    // Serial.print(average_encoder);
    // Serial.print("          x          ");

    // Serial.print("error_FR = ");
    // Serial.print(delta_FR - average_delta);
    // Serial.print("          ");

    // Serial.print("error_BL = ");
    // Serial.print(delta_BL - average_delta);
    // Serial.print("          x          ");

    // Serial.print("encoder FR = ");
    // Serial.print(en_FR);
    // Serial.print("          ");

    // Serial.print("encoder BL = ");
    // Serial.print(en_BL);
    // Serial.print("          ");

    // Serial.print("average_delta = ");
    // Serial.print(average_delta);
    // Serial.print("          ");

    // Serial.print("delta_FR = ");
    // Serial.print(delta_FR);
    // Serial.print("          ");

    // Serial.print("delta_BL = ");
    // Serial.print(delta_BL);

    // Serial.print("          x          ");

    // Serial.print("output_FR = ");
    // Serial.print(base_speed + output_FR);
    // Serial.print("          ");

    // Serial.print("output_BL = ");
    // Serial.print(base_speed + output_BL);
    // Serial.print("          ");

    Serial.print("\n");
  }
  distance = 0;
  if (direction == "FL") {
    position_x -= average_encoder / 370;
    position_y += average_encoder / 370;
  } else if (direction == "BR") {
    position_x += average_encoder / 370;
    position_y -= average_encoder / 370;
  }
  over_encoder_FR = tick - abs(en_FR);
  over_encoder_FL = tick - abs(en_FL);
  over_encoder_BR = tick - abs(en_BR);
  over_encoder_BL = tick - abs(en_BL);
  key_overencoder = 0;
}
