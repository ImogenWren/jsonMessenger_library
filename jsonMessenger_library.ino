/* jsonMessenger Library

_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
18/10/24


Version V0.0.0
- Focus on receiving & parsing incoming Serial messages in JSON format


*/


/* Version V0.0.0
Sketch uses 15604 bytes (50%) of program storage space. Maximum is 30720 bytes.
Global variables use 843 bytes (41%) of dynamic memory, leaving 1205 bytes for local variables. Maximum is 2048 bytes.
- Without Sprintf outside library
- Just about functional within library, but non functional outside library


// With sprintf
Sketch uses 15936 bytes (51%) of program storage space. Maximum is 30720 bytes.
Global variables use 1097 bytes (53%) of dynamic memory, leaving 951 bytes for local variables. Maximum is 2048 bytes.
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
  //std::cout << ("command parsed by jsonMessenger") << std::endl;
    char printbuffer[128];
   // strcpy(printbuffer, "  Command Received, Data: ");
    char databuffer[16];
    if (nextState.data_type == EMPTY) {
      strcpy(databuffer, "No Data");
    } else if (nextState.data_type == INTEGER) {  // Example of how to deal with different datatypes returned from jsonMessenger object
      itoa(nextState.numeric, databuffer, 10);    // 10: base 10 // If integer copy integer to string
    } else if (nextState.data_type == FLOAT) {
      dtostrf(nextState.data, 2, 2, databuffer);
    } else if (nextState.data_type == CHAR_ARRAY) {
    strcpy(databuffer, nextState.msg);
    } else {
      std::cout << "Exception in Returned Data" << std::endl;
    }
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