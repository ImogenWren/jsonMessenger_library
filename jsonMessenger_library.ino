/* jsonMessenger Library

_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
18/10/24

Please see: https://github.com/ImogenWren/jsonMessenger_library for latest version and usage instructions
Version V1.0.0
- Focus on receiving & parsing incoming Serial messages in JSON format



*/


/* Version V0.1.0
Sketch uses 13414 bytes (43%) of program storage space. Maximum is 30720 bytes.
Global variables use 751 bytes (36%) of dynamic memory, leaving 1297 bytes for local variables. Maximum is 2048 bytes.
- Added queue and dequeue system for received messages

*/


#include "jsonMessenger.h"
#include <autoDelay.h>


jsonMessenger jsonRX;  // create a json messenger object to handle commands received over Serial connection

autoDelay printDelay;


void setup() {
  Serial.begin(115200);
  jsonRX.jsonBegin();
}




void loop() {

#if JSON_USE_SINGLE_FRAME == true
  jsonStateData nextState = jsonRX.jsonReadSerialLoop();  // If not using the queue function, then pass data from jsonMessenger object by passing values
#elif JSON_USE_QUEUE == true
  jsonRX.jsonReadSerialLoop();
#endif



#if JSON_USE_SINGLE_FRAME == true
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
  }
#endif

  if (printDelay.millisDelay(10000)) {
#if JSON_USE_QUEUE == true
    jsonStateData DQ_Data = jsonRX.dequeue_cmd();
    if (DQ_Data.cmd_received) {  // If command is received
      jsonRX.printJSONdata(&DQ_Data);
    }
#endif
  }
}
