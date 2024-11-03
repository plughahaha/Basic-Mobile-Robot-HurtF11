void Condition_XY(float x, float y) {
  static float last_x = 0;
  static float last_y = 0;

  // คำนวณความห่างระหว่างตำแหน่งปัจจุบันและตำแหน่งก่อนหน้า
  float distance_x = ((x - last_x));
  float distance_y = ((y - last_y));

  // แสดงค่าปัจจุบันของ x และ y
  Serial.print("Position = (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.println(")");

  // แสดงค่าความห่างระหว่างตำแหน่งปัจจุบันกับตำแหน่งก่อนหน้า
  Serial.print("Delta = (");
  Serial.print(distance_x);
  Serial.print(",");
  Serial.print(distance_y);
  Serial.println(")");
  Serial.println();

  // อัปเดตตำแหน่งก่อนหน้าให้เป็นตำแหน่งปัจจุบัน
  last_x = x;
  last_y = y;
  // FR FL BR BL
  if (distance_x != 0 && distance_y != 0) {
    if (distance_x > 0 && distance_y > 0) {
      Two_motor_FR("FR", abs(distance_x));
      motorstop();
    } else if (distance_x < 0 && distance_y < 0) {
      Two_motor_FR("BL", abs(distance_x));
      motorstop();
    }
    if (distance_x < 0 && distance_y > 0) {
      Two_motor_FL("FL", abs(distance_x));
      motorstop();
    } else if (distance_x > 0 && distance_y < 0) {
      Two_motor_FL("BR", abs(distance_x));
      motorstop();
    }

    // SL SR
  } else if (distance_x != 0) {
    if (distance_x > 0 && distance_y == 0 ) {
      Control_movement("SR", distance_x);
      motorstop();
    } else if (distance_x < 0 && distance_y == 0 ) {
      Control_movement("SL", abs(distance_x));
      motorstop();
    }
    // F B
  } else if (distance_y != 0) {
    if (distance_y > 0 && distance_x == 0) {
      Control_movement("Forward", distance_y);
      motorstop();
    } else if (distance_y < 0 && distance_x == 0 ) {
      Control_movement("Backward", abs(distance_y));
      motorstop();
    }
  }
}


