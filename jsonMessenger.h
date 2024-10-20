/* jsonMessenger.h
_Library to simplify two way communication over Serial interfaces using JSON formatted messages_

Imogen Heard
17/10/24

Please see: https://github.com/ImogenWren/jsonMessenger_library for latest version and usage instructions

Version V1.0.0
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


#include <stdio.h>
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
  // StaticJsonDocument<JSON_RX_SIZE> jsonRXdoc;  // This is the JSON object
  //JsonDocument doc;  // This version for V7.x.x Dynamically assigned memory



public:
  // constructor
  jsonMessenger();

  void jsonBegin();

  jsonStateData jsonReadSerialLoop();  // function needs to be called periodically to accept incoming serial messages, parse & return jsonStateData with new state /and data required for new state

  void printJSON(StaticJsonDocument<JSON_RX_SIZE> jsonDoc);  // Prints the static jsonRXdoc


  void printCMDkey(jsonStates state);  // to print the state in human readable form without coping the entire list of keys to global scope

  void printDataType(dataTypes type);

    private:
};



#endif
