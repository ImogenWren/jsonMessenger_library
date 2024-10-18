

//#pragma once

#ifndef jsonConfig_h
#define jsonConfig_h


#include <ArduinoSTL.h>            // [Arduino Library Manager]
#include <iostream>                // [std::iostream]
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
  { NONE, EMPTY },
  { FAN_A0, INTEGER },
  { FAN_A1, INTEGER },
  { FAN_A2, INTEGER },
  { FAN_A3, INTEGER },
  { FAN_A4, INTEGER },
  { FAN_B0, INTEGER },
  { FAN_B1, INTEGER },
  { FAN_B2, INTEGER },
  { FAN_B3, INTEGER },
  { FAN_B4, INTEGER },
  { FAN_C0, INTEGER },
  { FAN_C1, INTEGER },
  { FAN_C2, INTEGER },
  { FAN_C3, INTEGER },
  { FAN_C4, INTEGER },
  { FAN_D0, INTEGER },
  { FAN_D1, INTEGER },
  { FAN_D2, INTEGER },
  { FAN_D3, INTEGER },
  { FAN_D4, INTEGER },
  { FAN_E0, INTEGER },
  { FAN_E1, INTEGER },
  { FAN_E2, INTEGER },
  { FAN_E3, INTEGER },
  { FAN_E4, INTEGER },
  { ALL, INTEGER },
  { MOD, INTEGER },
  { USR, CHAR_ARRAY }
};


// Then Declare a list of key commands that will be required to be parsed. This must match the order of the enums above
static char jsonCommandKeys[][4] = {
  "NULL",
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
}


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