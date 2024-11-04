void Special_condition(String type) {
  if (type == "Home") {
    Condition_XY(0, -1);
    Condition_XY(1, -1);
    Condition_XY(1, 0);
    Condition_XY(0, 0);
    Condition_XY(0.5, 0.5);
    Condition_XY(1, 0);
  }
}