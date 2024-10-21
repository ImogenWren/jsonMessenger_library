

//#pragma once

#ifndef jsonConfig_h
#define jsonConfig_h


#include <ArduinoSTL.h>            // [Arduino Library Manager]
//#include <iostream>                // [std::iostream]
#include <map>                     // [std::map]


#define JSON_RX_SIZE 48


// Define an enum to define variable types, These will be linked to a state enum so when a keyword is received, we can look up what data type should be sent with it
typedef enum {  // enum to pass variable types between functions
  EMPTY,
  INTEGER,
  FLOAT,
  CHAR_ARRAY
} dataTypes;

// For human readability of enum above
static char typeNames[][12] = {
  "EMPTY",
  "INTEGER",
  "FLOAT",
  "CHAR_ARRAY"
};


// Define list of typical commands for system for future reference
/*
{"A0": 100}
{"A1": 98}
{"all": "stop"}
{"all":0}





*/
// Declare a list of all possible key values as ENUM. These values will be passed out of the jsonMessenger Object and can be used to go to different states
// NOTE this list may not include all possible states, JUST the states that are triggered by receiving a command, including a null value at 0
typedef enum {
  NONE,
  FAN_A0,
  FAN_A1,
  FAN_A2,
  FAN_A3,
  FAN_A4,
  FAN_B0,
  FAN_B1,
  FAN_B2,
  FAN_B3,
  FAN_B4,
  FAN_C0,
  FAN_C1,
  FAN_C2,
  FAN_C3,
  FAN_C4,
  FAN_D0,
  FAN_D1,
  FAN_D2,
  FAN_D3,
  FAN_D4,
  FAN_E0,
  FAN_E1,
  FAN_E2,
  FAN_E3,
  FAN_E4,
  ALL,
  MOD,
  USR,
  NUM_VALUES  // Add sentinal NUM_VALUES to count number of elements
} jsonStates;


// Now Link each jsonState ENUM with the datatype ENUM in a map structure.
//In this example most will be integers, but will include some cstrings to test
const std::map<jsonStates, dataTypes> jsonStateMap = {
  { jsonStates::NONE, dataTypes::EMPTY },
  { jsonStates::FAN_A0, dataTypes::INTEGER },
  { jsonStates::FAN_A1, dataTypes::INTEGER },
  { jsonStates::FAN_A2, dataTypes::INTEGER },
  { jsonStates::FAN_A3, dataTypes::INTEGER },
  { jsonStates::FAN_A4, dataTypes::INTEGER },
  { jsonStates::FAN_B0, dataTypes::INTEGER },
  { jsonStates::FAN_B1, dataTypes::INTEGER },
  { jsonStates::FAN_B2, dataTypes::INTEGER },
  { jsonStates::FAN_B3, dataTypes::INTEGER },
  { jsonStates::FAN_B4, dataTypes::INTEGER },
  { jsonStates::FAN_C0, dataTypes::INTEGER },
  { jsonStates::FAN_C1, dataTypes::INTEGER },
  { jsonStates::FAN_C2, dataTypes::INTEGER },
  { jsonStates::FAN_C3, dataTypes::INTEGER },
  { jsonStates::FAN_C4, dataTypes::INTEGER },
  { jsonStates::FAN_D0, dataTypes::INTEGER },
  { jsonStates::FAN_D1, dataTypes::INTEGER },
  { jsonStates::FAN_D2, dataTypes::INTEGER },
  { jsonStates::FAN_D3, dataTypes::INTEGER },
  { jsonStates::FAN_D4, dataTypes::INTEGER },
  { jsonStates::FAN_E0, dataTypes::INTEGER },
  { jsonStates::FAN_E1, dataTypes::INTEGER },
  { jsonStates::FAN_E2, dataTypes::INTEGER },
  { jsonStates::FAN_E3, dataTypes::INTEGER },
  { jsonStates::FAN_E4, dataTypes::INTEGER },
  { jsonStates::ALL, dataTypes::INTEGER },
  { jsonStates::MOD, dataTypes::FLOAT },
  { jsonStates::USR, dataTypes::CHAR_ARRAY }
};


// Then Declare a list of key commands that will be required to be parsed. This must match the order of the enums above
static char jsonCommandKeys[][6] = {
  "none",
  "A0", "A1", "A2", "A3", "A4",
  "B0", "B1", "B2", "B3", "B4",
  "C0", "C1", "C2", "C3", "C4",
  "D0", "D1", "D2", "D3", "D4",
  "E0", "E1", "E2", "E3", "E4",
  "all", "mod", "usr"
};
// NOTE, this can also be used to turn the enums above back into strings for human readability

// Also including generic keys, these are used for more verbose JSON commands like:
// {"set": "item", "to":"value"}
static char jsonGenerics[][6] = {
  "NULL",
  "set",
  "to",
  "get"
};



// Finally Declare a structure that will hold both the jsonStates enum, and any data that will need to be passed from jsonMessenger, into the states.
// We can make this fairly generic by including additional datatypes, or we can reduce the size of the memory used by removing the unneeded ones
struct jsonStateData {
  jsonStates cmdState;        // The command state enum to tell state machine what state to go to next
  dataTypes data_type;        // The type of data being passed along with structure (though state should know what data to expect anyway), this could be removed to save space
  int numeric;                // empty generic data slots for each data type
  float data;
  char msg[16];
  bool cmd_received;           // Flag set true by jsonLoop when cmd is received
};



#endif