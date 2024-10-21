/* jsonMessenger Library

_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
18/10/24

Please see: https://github.com/ImogenWren/jsonMessenger_library for latest version and usage instructions
Version V1.0.0
- Focus on receiving & parsing incoming Serial messages in JSON format



*/


/* Version V0.0.0
Sketch uses 14690 bytes (47%) of program storage space. Maximum is 30720 bytes.
Global variables use 831 bytes (40%) of dynamic memory, leaving 1217 bytes for local variables. Maximum is 2048 bytes.
- working apart from looking up the state name back as a string
- likewise with data type


Sketch uses 14896 bytes (48%) of program storage space. Maximum is 30720 bytes.
Global variables use 1005 bytes (49%) of dynamic memory, leaving 1043 bytes for local variables. Maximum is 2048 bytes.
- 174 more bytes just because of     Serial.print(jsonCommandKeys[next_state]);
- brings it into global scope?


*/


#include "jsonMessenger.h"
#include <autoDelay.h>
//#include <ArduinoSTL.h>  // [Arduino Library Manager]
//#include <iostream>      // [std::iostream]

jsonMessenger jsonRX;  // create a json messenger object to handle commands received over Serial connection

autoDelay printDelay;
/*
struct jsonStateData {
  jsonStates cmdState;        // The command state enum to tell state machine what state to go to next
  dataTypes data_type;        // The type of data being passed along with structure (though state should know what data to expect anyway), this could be removed to save space
  int numeric;                // empty generic data slots for each data type
  float data;
  char msg[16];
  bool cmd_received;
};
{NONE, EMPTY, 0, 0.0, "", false};  // This is what the empty data structure should loo
*/

//#define BOARD_TYPE NANO
//#include <trackRAM.h>

//trackRAM ram;

void setup() {
  Serial.begin(115200);
  //  ram.begin();
  //  ram.getPrintStats("setup");
  jsonRX.jsonBegin();
  Serial.println(F("end of setup"));
}


/*
  EMPTY,
  INTEGER,
  FLOAT,
  CHAR_ARRAY
*/


void loop() {


  jsonStateData nextState = jsonRX.jsonReadSerialLoop();


  if (nextState.cmd_received) {  // If command is received



    //char printbuffer[128];
    // strcpy(printbuffer, "  Command Received, Data: ");
    char loopdatabuffer[16];
    if (nextState.data_type == EMPTY) {
      strcpy(loopdatabuffer, "No Data");
    } else if (nextState.data_type == INTEGER) {    // Example of how to deal with different datatypes returned from jsonMessenger object
      itoa(nextState.numeric, loopdatabuffer, 10);  // 10: base 10 // If integer copy integer to string
    } else if (nextState.data_type == FLOAT) {
      dtostrf(nextState.data, 2, 2, loopdatabuffer);
    } else if (nextState.data_type == CHAR_ARRAY) {
      strcpy(loopdatabuffer, nextState.msg);
    } else {
      std::cout << "Exception in Returned Data" << std::endl;
    }

    jsonRX.printCMDkey(nextState.cmdState);
   // Serial.print(jsonCommandKeys[next_state]);
    Serial.print(" cmd Received, Data Type: ");
    // Serial.print(typeNames[next_type]);
    jsonRX.printDataType(nextState.data_type);
    Serial.print(" data: ");
    Serial.println(loopdatabuffer);

    // std::cout <<  nextState.cmdState << " command parsed, Data: " << loopdatabuffer << std::endl;

    // strcat(jsonCommandKeys[nextState.cmdState], printbuffer);
    // Serial.println(nextState.cmdState);
    // strcat(printbuffer, databuffer);
    // snprintf(printbuffer, 64, "cmd: %s, data_type: %s, data: %s", nextState.cmdState,  nextState.data_type, databuffer);
    //  std::cout << printbuffer << std::endl;
    // Serial.println(printbuffer);
  }

  if (printDelay.millisDelay(5000)) {
    //   ram.getPrintStats("loop");
    Serial.println(F("Alive and Loop"));
  }
}