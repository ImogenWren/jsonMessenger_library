//#include "PCA9685.h"
//#include <Wire.h>

#include "jsonMessenger.h"
#include <autoDelay.h>
//#include <ArduinoSTL.h>  // [Arduino Library Manager]
//#include <iostream>      // [std::iostream]

jsonMessenger jsonRX; // create a json messenger object to handle commands received over Serial connection

autoDelay printDelay;
/*
struct jsonStateData {
  jsonStates cmdState;
  int numeric;
  float data;
  char msg[16];
  bool cmd_received;    // Flag set true by jsonLoop when cmd is received
};
*/

void setup() {
  Serial.begin(115200);

  jsonRX.jsonBegin();              
  Serial.println("end of setup");
}



void loop() {


  jsonStateData nextState = jsonRX.jsonReadSerialLoop();

  if (nextState.cmd_received) {     // If command is received 
    char buffer[64];
    char databuffer[8];
    if (nextState.data_type == INTEGER) { // Example of how to deal with different datatypes returned from jsonMessenger object
    }
    //
    //dtostrf(nextState.data, 2, 2, databuffer);
    //sprintf(buffer, "cmd: %s, Numeric: %i, Data: %s, msg: %s", jsonCommandKeys[nextState.cmdState], nextState.numeric, databuffer, nextState.msg);
  }

  if (printDelay.millisDelay(5000)) {
    // std::cout << "alive" << std::endl;
    //Serial.println("Alive and Loop");
  }
}