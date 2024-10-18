/*

void old_setup() {
  Serial.print("Testing Array: C2: ");
  Serial.print(PWM_array[C][2]);
  delay(4000);
  Serial.println("\nPrinting 2D array: ");
  print_2d_array(PWM_array);
  delay(10000);

  bank_A.init(BANK_A_ADDRESS);
  bank_B.init(BANK_B_ADDRESS);

  // Set freq to 100Hz, range from 24Hz~1526hz
  bank_A.setFrequency(PWM_FREQUENCY);
  bank_B.setFrequency(PWM_FREQUENCY);

  Serial.println("Setting Outputs");
  update_pwm_from_array(PWM_array);
  delay(50000);
  while (1)
    ;
}




#define INTERVAL 50

void old_loop() {
  brightness = brightness + INTERVAL;
  if (brightness >= MAX_VAL) {
    brightness = 0;
  }
  Serial.println(brightness);

  for (int i = 1; i < 17; i++) {
    bank_A.setPwm(i, 0, brightness);
  }

  for (int i = 1; i < 17; i++) {
    bank_B.setPwm(i, 0, MAX_VAL - brightness);
  }
}


*/