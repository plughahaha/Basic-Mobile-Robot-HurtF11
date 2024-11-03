
void Control_movement(String direction, int distance) {
  // static double position_x = 0;
  // static double position_y = 0;
  encoder_FR.reset();
  encoder_BL.reset();
  encoder_BR.reset();
  encoder_FL.reset();
  average_encoder = 0;
  average_delta = 0;
  en_FL = 0;
  en_FR = 0;
  en_BL = 0;
  en_BR = 0;
  integral_FR = 0;
  integral_FL = 0;
  integral_BL = 0;
  integral_BR = 0;
  previous_error_FL = 0;
  previous_error_FR = 0;
  previous_error_BL = 0;
  previous_error_BR = 0;
  error_FL = 0;
  error_FR = 0;
  error_BL = 0;
  error_BR = 0;
  output_FL = 0;
  output_FR = 0;
  output_BL = 0;
  output_BR = 0;
  delta_FL = 0;
  delta_FR = 0;
  delta_BL = 0;
  delta_BR = 0;
  cal_delta_FL = 0;
  cal_delta_FR = 0;
  cal_delta_BL = 0;
  cal_delta_BR = 0;
  //  double tick = (distance / 8) * 4000;
  tick = distance * (125);
  average_encoder = 0;

  previous_time = millis();

  while (average_encoder < tick) {
    current_time = (millis() - previous_time)/1000 ; 

    en_FL = encoder_FL.getCount();
    en_FR = encoder_FR.getCount();
    en_BL = encoder_BL.getCount();
    en_BR = encoder_BR.getCount();
    average_encoder = (abs(en_FL) + abs(en_FR) + abs(en_BL) + abs(en_BR)) / 4;

    delta_FL = tick - abs(en_FL);
    delta_FR = tick - abs(en_FR);
    delta_BL = tick - abs(en_BL);
    delta_BR = tick - abs(en_BR);
    average_delta = (abs(delta_FL) + abs(delta_FR) + abs(delta_BL) + abs(delta_BR)) / 4;

    // Cal delta for FL
    if (delta_FL > average_delta) {
      cal_delta_FL = delta_FL - average_delta;
      if (cal_delta_FL < 10) {
        error_FL = 0;
      }
      if (cal_delta_FL > 10) {
        error_FL = 1;
      }
      if (cal_delta_FL > 100) {
        error_FL = 2;
      }
      if (cal_delta_FL > 200) {
        error_FL = 3;
      }
      if (cal_delta_FL > 500) {
        error_FL = 5;
      }
      if (cal_delta_FL > 1000) {
        error_FL = 7;
      }
    }

    if (delta_FL < average_delta) {
      cal_delta_FL = average_delta - delta_FL;
      if (cal_delta_FL < 10) {
        error_FL = 0;
      }
      if (cal_delta_FL > 10) {
        error_FL = -1;
      }
      if (cal_delta_FL > 100) {
        error_FL = -2;
      }
      if (cal_delta_FL > 200) {
        error_FL = -3;
      }
      if (cal_delta_FL > 500) {
        error_FL = -5;
      }
      if (cal_delta_FL > 1000) {
        error_FL = -7;
      }
    }

    // Cal delta for FR
    if (delta_FR > average_delta) {
      cal_delta_FR = delta_FR - average_delta;
      if (cal_delta_FR < 10) {
        error_FR = 0;
      }
      if (cal_delta_FR > 10) {
        error_FR = 1;
      }
      if (cal_delta_FR > 100) {
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
      if (cal_delta_FR < 10) {
        error_FR = 0;
      }
      if (cal_delta_FR > 10) {
        error_FR = -1;
      }
      if (cal_delta_FR > 100) {
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
      if (cal_delta_BL < 10) {
        error_BL = 0;
      }
      if (cal_delta_BL > 10) {
        error_BL = 1;
      }
      if (cal_delta_BL > 100) {
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
      if (cal_delta_BL < 10) {
        error_BL = 0;
      }
      if (cal_delta_BL > 10) {
        error_BL = -1;
      }
      if (cal_delta_BL > 100) {
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

    // Cal delta for BR
    if (delta_BR > average_delta) {
      cal_delta_BR = delta_BR - average_delta;
      if (cal_delta_BR < 10) {
        error_BR = 0;
      }
      if (cal_delta_BR > 10) {
        error_BR = 1;
      }
      if (cal_delta_BR > 100) {
        error_BR = 2;
      }
      if (cal_delta_BR > 200) {
        error_BR = 3;
      }
      if (cal_delta_BR > 500) {
        error_BR = 5;
      }
      if (cal_delta_BR > 1000) {
        error_BR = 7;
      }
    }

    if (delta_BR < average_delta) {
      cal_delta_BR = average_delta - delta_BR;
      if (cal_delta_BR < 10) {
        error_BR = 0;
      }
      if (cal_delta_BR > 10) {
        error_BR = -1;
      }
      if (cal_delta_BR > 100) {
        error_BR = -2;
      }
      if (cal_delta_BR > 200) {
        error_BR = -3;
      }
      if (cal_delta_BR > 500) {
        error_BR = -5;
      }
      if (cal_delta_BR > 1000) {
        error_BR = -7;
      }
    }

    output_FL = (Kp_FL * error_FL) + (Ki_FL * integral_FL) + (Kd_FL * (error_FL - previous_error_FL));
    output_FL = constrain(output_FL, -255, 255);
    output_FR = (Kp_FR * error_FR) + (Ki_FR * integral_FR) + (Kd_FR * (error_FR - previous_error_FL));
    output_FR = constrain(output_FR, -255, 255);
    output_BL = (Kp_BL * error_BL) + (Ki_BL * integral_BL) + (Kd_BL * (error_BL - previous_error_FL));
    output_BL = constrain(output_BL, -255, 255);
    output_BR = (Kp_BR * error_BR) + (Ki_BR * integral_BR) + (Kd_BR * (error_BR - previous_error_FL));
    output_BR = constrain(output_BR, -255, 255);

    if (direction == "Forward") {
      motor_FR.speed(base_speed + output_FR);
      motor_FL.speed(base_speed + output_FL);
      motor_BL.speed(base_speed + output_BL);
      motor_BR.speed(base_speed + output_BR);
    } else if (direction == "Backward") {
      motor_FR.speed((base_speed + output_FR) * -1);
      motor_FL.speed((base_speed + output_FL) * -1);
      motor_BL.speed((base_speed + output_BL) * -1);
      motor_BR.speed((base_speed + output_BR) * -1);
    } else if (direction == "SL") {
      motor_FR.speed((base_speed + output_FR));
      motor_FL.speed((base_speed + output_FL) * -1);
      motor_BL.speed((base_speed + output_BL));
      motor_BR.speed((base_speed + output_BR) * -1);
    } else if (direction == "SR") {
      motor_FR.speed((base_speed + output_FR) * -1);
      motor_FL.speed((base_speed + output_FL));
      motor_BL.speed((base_speed + output_BL) * -1);
      motor_BR.speed((base_speed + output_BR));
    }
    integral_FL += error_FL;
    previous_error_FL = error_FL;
    integral_FR += error_FR;
    previous_error_FR = error_FR;
    integral_BL += error_BL;
    previous_error_BL = error_BL;
    integral_BR += error_BR;
    previous_error_BR = error_BR;

    // if (direction == "Forward" || direction == "Backward") {
    //   current_x += average_encoder / 125;
    // }

    Serial.print("Current Time = ");
    Serial.print(current_time);
    Serial.print("          ");

    Serial.print("Current Speed = ");
    Serial.print(posi/current_time);

    Serial.print("          ");

    if (direction == "Forward") {
      Serial.print("current = (");
      Serial.print(position_x);
      Serial.print(",");
      posi = position_y + int(average_encoder / 125) ;
      Serial.print(posi);
      Serial.print(")");
      Serial.print("          ");
    }
    if (direction == "SL") {

      Serial.print("current = (");
      Serial.print(position_x - int(average_encoder / 125));
      Serial.print(",");
      Serial.print(position_y);
      Serial.print(")");
      Serial.print("          ");

    } else if (direction == "SR") {

      Serial.print("current = (");
      Serial.print(position_x + int(average_encoder / 125));
      Serial.print(",");
      Serial.print(position_y);
      Serial.print(")");
      Serial.print("          ");
    } else if (direction == "Backward") {
      Serial.print("current = (");
      Serial.print(position_x);
      Serial.print(",");
      Serial.print(position_y - int(average_encoder / 125));
      Serial.print(")");
      Serial.print("          ");
    }



    Serial.print("tick = ");
    Serial.print(tick);
    Serial.print("          ");

    Serial.print("average_encoder = ");
    Serial.print(average_encoder);
    Serial.print("          ");

    Serial.print("distance = ");
    Serial.print(average_encoder / 125);
    Serial.print("          x          ");

    Serial.print("error_FL = ");
    Serial.print(delta_FL - average_delta);
    Serial.print("          ");

    Serial.print("error_FR = ");
    Serial.print(delta_FR - average_delta);
    Serial.print("          ");

    Serial.print("error_BL = ");
    Serial.print(delta_BL - average_delta);
    Serial.print("          ");

    Serial.print("error_BR = ");
    Serial.print(delta_BR - average_delta);
    Serial.print("          x          ");

    Serial.print("encoder FL = ");
    Serial.print(en_FL);
    Serial.print("          ");

    Serial.print("encoder FR = ");
    Serial.print(en_FR);
    Serial.print("          ");

    Serial.print("encoder BL = ");
    Serial.print(en_BL);
    Serial.print("          ");

    Serial.print("encoder BR = ");
    Serial.print(en_BL);
    Serial.print("          x          ");

    Serial.print("average_delta = ");
    Serial.print(average_delta);
    Serial.print("          ");

    Serial.print("delta_FL = ");
    Serial.print(delta_FL);
    Serial.print("          ");

    Serial.print("delta_FR = ");
    Serial.print(delta_FR);
    Serial.print("          ");

    Serial.print("delta_BL = ");
    Serial.print(delta_BL);
    Serial.print("          ");

    Serial.print("delta_BR = ");
    Serial.print(delta_BR);
    Serial.print("          x          ");

    Serial.print("output_FL = ");
    Serial.print(base_speed + output_FL);
    Serial.print("          ");

    Serial.print("output_FR = ");
    Serial.print(base_speed + output_FR);
    Serial.print("          ");

    Serial.print("output_BL = ");
    Serial.print(base_speed + output_BL);
    Serial.print("          ");

    Serial.print("output_BR = ");
    Serial.print(base_speed + output_BR);

    Serial.print("\n");
  }
  distance = 0;
  if (direction == "Forward") {
    position_y += average_encoder / 125;
  } else if (direction == "Backward") {
    position_y -= average_encoder / 125;
  }
  if (direction == "SL") {
    position_x -= average_encoder / 125;
  } else if (direction == "SR") {
    position_x += average_encoder / 125;
  }
}
