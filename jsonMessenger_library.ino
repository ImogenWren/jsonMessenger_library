/* jsonMessenger Library

_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
18/10/24


Version V0.0.0
- Focus on receiving & parsing incoming Serial messages in JSON format


*/


#include "jsonMessenger.h"
#include <autoDelay.h>
#include <ArduinoSTL.h>  // [Arduino Library Manager]
#include <iostream>      // [std::iostream]

jsonMessenger jsonRX;  // create a json messenger object to handle commands received over Serial connection

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

  if (nextState.cmd_received) {  // If command is received
    char buffer[64];
    char databuffer[8];
    if (nextState.data_type == INTEGER) {       // Example of how to deal with different datatypes returned from jsonMessenger object
      itoa(nextState.numeric, dataBuffer, 10);  // 10: base 10 // If integer copy integer to string
    } else if (nextState.data_type == ){

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