/* jsonMessenger.h
_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
17/10/24


Version V0.0.0
- Focus on receiving & parsing incoming Serial messages in JSON format


*/

//#pragma once

#ifndef jsonMessenger_h
#define jsonMessenger_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include <ArduinoJson.h>
#include "jsonConfig.h"



//extern char jsonCommandKeys[][4];



// These variables relate to the JSON report that is printed to serial monitor to report sensor data & all statuses to UI
//#define JSON_TX_SIZE 620
//StaticJsonDocument<JSON_TX_SIZE> jsonTX;


class jsonMessenger {
private:
  //# JSON Varibles & Object Declaration
  // These variables relate to incoming serial commands
  // was 64 reduced to save space
  StaticJsonDocument<JSON_RX_SIZE> jsonRXdoc;  // This is the JSON object
  //JsonDocument doc;  // This version for V7.x.x Dynamically assigned memory



public:
  // constructor
  jsonMessenger();

  void jsonBegin();

  jsonStateData jsonReadSerialLoop();  // function needs to be called periodically to accept incoming serial messages, parse & return jsonStateData with new state /and data required for new state

  void printJSON();  // Prints the static jsonRXdoc




private:


};



#endif
