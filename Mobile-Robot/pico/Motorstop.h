void motorstop() {
  int timer0 = millis();
  while (millis() - timer0 < 100) {
    motor_FL.stop();
    motor_FR.stop();
    motor_BL.stop();
    motor_BR.stop();
    // Serial.print("Current Position (X,Y) = (");
    // Serial.print((position_x) / 100);
    // Serial.print(" m,");
    // Serial.print(position_y / 100);
    // Serial.print(" m)");
    // Serial.print("          ");
    // if (average_encoder > tick) {
    //   velocity = 0;
    // }
    // Serial.print("Velocity = ");
    // Serial.print(velocity);
    // Serial.println(" m/s");
  }
}