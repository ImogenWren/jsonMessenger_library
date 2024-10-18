/*
uint16_t brightness = 0;
#define MAX_VAL 4096
#define MID_POINT 2048

PCA9685 bank_A;
PCA9685 bank_B;

#define BANK_A_ADDRESS 0x7F
#define BANK_B_ADDRESS 0x7E

#define PWM_FREQUENCY 1500

// Define 5x5 array/matrix for storing PWM vals
// Vertical Axis is A to E
// Hoz Axis 0 to 4

//#define A 0
//#define B 1
//#define C 2
//#define D 3
//#define E 4


uint16_t PWM_array[5][5] = {

  { 5, 6, 7, 8, 9 },

  { 20, 21, 22, 23, 24 },

  { 50, 51, 52, 53, 54 },

  { 65, 66, 67, 68, 69 },

  { 120, 121, 122, 123, 124 }

};

void print_2d_array(uint16_t array2d[5][5]) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      Serial.print(array2d[i][j]);
      Serial.print(", ");
    }
    Serial.println("");
  }
}

char ch_name_array[6][6] = {
  "A",
  "B",
  "C",
  "D",
  "E"
};

void update_pwm_from_array(uint16_t pwmArray[5][5]) {
  // Update the first 15 values to bank_A
  Serial.println("Setting:");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      int channel = i * 5 + j;
      int pwm_val = pwmArray[i][j];
      Serial.print("|");
      Serial.print(ch_name_array[i]);
      Serial.print(j);
      Serial.print(" ch");
      Serial.print(channel);
      Serial.print(" to ");
      Serial.print(pwm_val);
      bank_A.setPwm(i, pwm_val, 0);
    }
    Serial.println();
  }
  // Update the last 10 values to bank_B
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      int iterator = i + 3;
      int channel = i * 5 + j;
      int pwm_val = pwmArray[iterator][j];
      Serial.print("|");
      Serial.print(ch_name_array[iterator]);
      Serial.print(j);
      Serial.print(" ch");
      Serial.print(channel);
      Serial.print(" to ");
      Serial.print(pwm_val);
      bank_B.setPwm(iterator, pwm_val, 0);
    }
    Serial.println();
  }
}


#include "stateMachine.h"


void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Serial.begin(115200);
  Serial.println("25ch PWM Fan Driver");

  
  
}


void loop() {
  readSerialJSON()
}

*/