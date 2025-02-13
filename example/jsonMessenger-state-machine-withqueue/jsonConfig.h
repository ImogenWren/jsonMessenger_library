/*  jsonConfig.h

This header should be used with the jsonMessenger library to define all the working states & commands that can be decoded by the jsonMessenger system.

This library is designed to parse commands recieved via the Serial object in Arduino. Commands should be formatted in CMD:VALUE pairs as follows:

Version 1 -> succinct command structure
`{"CMD":"VALUE"}` -> for CMDs with passed values
or
`{"CMD":0} -> for CMDs with no additional values
note: in the 2nd example, any data entered after : will be ignored, as we have already defined the datatypes that will be passed with each command to the parser,
 however some data should be included to prevent errors in parsing JSON commands

Version 2 -> Verbose command structure
`{"set":"CMD","to":"VALUE"} -> for CMDs with passed values
or
`{"set":"CMD"} -> for CMDs with no additional data.

As the libary works via parsing JSON structures, any additional key:value pairs will simply be ignored, as long as the overal JSON structure is validated, the parser will just look
for the existance of matching keys, and ignore anything else.


Please see: https://github.com/ImogenWren/jsonMessenger_library for latest version and usage instructions, or follow the numbered comments for an
explanation of how to modify this template for other uses. 

All modifications to jsonMessgender should be carried out in this header file `jsonConfig.h`, please do not modify jsonMessenger.h or jsonMessenger.cpp!

Imogen Heard
21/10/2024


*/

//#pragma once

#ifndef jsonConfig_h
#define jsonConfig_h



#define JSON_USE_QUEUE true        //If true, library uses queueing, and jsonStateData should be passed from the dequeue function.
                                    // if false, library will respond to each command individually and the jsonStateData is passed from jsonReadSerialLoop function
#define CMD_QUEUE_LENGTH 10   // Max length of CMD_QUEUE if activated

#define DEBUG_JSON_MESSENGER false  // Prints debugging messages


#define JSON_RX_SIZE 32     // Size of the buffer to hold incoming JSON formatted commands to be parsed
#define JSON_MSG_LENGTH 12  // Length of msg array in json data structure


// 1. Define an enum to define variable type used, These will be linked to a state enum so when a keyword is received, we can look up what data type should be sent with it

typedef enum {  // enum to pass variable types between functions
  EMPTY,
  INTEGER,
  FLOAT,
  CSTRING,
  BOOL
} dataTypes;

// 1b. Place these enums into an array to enable lookup by index (This shouldnt be nessissary but it fixed a bug at one point)
const dataTypes dataTypes_array[5] = { EMPTY, INTEGER, FLOAT, CSTRING, BOOL };


// 1c. List the same enums as cStrings, this will enable human readability of enum above
static char typeNames[][8] = {
  "EMPTY",
  "INTEGER",
  "FLOAT",
  "CSTRING",
  "BOOL"
};


// 2. Declare a list of all possible key values as ENUM. These values will be passed out of the jsonMessenger Object and can be used to trigger different states
// NOTE: this list may not include all possible states for the state machine, JUST the states that are triggered by receiving a command.
// - Include a null value at 0 -> This is because this enum will be initialised at 0 to represent jsonMessenger not receiving data, or being unable to parse a command

typedef enum {
  NONE,  // Include null or none state
  STOP,
  START,
  SET_SPEED_HZ,
  SET_SPEED_RPM,
  HOME,
  CALIBRATE,
  FREEWHEEL,
  BRAKE,
  GOTO,
  SAMPLERATE,
  STARTSTREAM,
  STOPSTREAM,
  SNAPSHOT,
  SNAPTIME,
  PING,
  STATUS,
  HELP,
  NUM_VALUES  // Add sentinal NUM_VALUES to count number of elements, this is very important and will be used to size for loops inside the jsonMessenger object
} jsonStates;


// 3. Link each jsonState ENUM with the datatype ENUM in a ~~map~~<depreciated> structure -> Now uses 2D array!.
//const std::map<jsonStates, dataTypes> jsonStateMap = {  // Old version

const uint16_t jsonStateMap[NUM_VALUES][2] = {
  { jsonStates::NONE, dataTypes::EMPTY },
  { jsonStates::STOP, dataTypes::EMPTY },
  { jsonStates::START, dataTypes::EMPTY },
  { jsonStates::SET_SPEED_HZ, dataTypes::FLOAT },
  { jsonStates::SET_SPEED_RPM, dataTypes::FLOAT },
  { jsonStates::HOME, dataTypes::EMPTY },
  { jsonStates::CALIBRATE, dataTypes::EMPTY },
  { jsonStates::FREEWHEEL, dataTypes::EMPTY },
  { jsonStates::BRAKE, dataTypes::EMPTY },
  { jsonStates::GOTO, dataTypes::INTEGER },
  { jsonStates::SAMPLERATE, dataTypes::INTEGER },
  { jsonStates::STARTSTREAM, dataTypes::EMPTY },
  { jsonStates::STOPSTREAM, dataTypes::EMPTY },
  { jsonStates::SNAPSHOT, dataTypes::EMPTY },
  { jsonStates::SNAPTIME, dataTypes::INTEGER },
  { jsonStates::PING, dataTypes::EMPTY },
  { jsonStates::STATUS, dataTypes::EMPTY },
  { jsonStates::HELP, dataTypes::EMPTY }
};




// 4. Declare a list of key commands that will be required to be parsed. This must match the order of the enums above
static char jsonCommandKeys[][7] = {
  "na",
  "stop",
  "start",
  "hz",
  "rpm",
  "home",
  "cal",
  "free",
  "brake",
  "goto",
  "sample",
  "stream",
  "endst",
  "snap",
  "time",
  "ping",
  "status",
  "help"
};
// NOTE, this can also be used to turn the enums above back into strings for human readability

//<depreciated>
// Also including generic keys, these are used for more verbose JSON commands like:
// {"set": "item", "to":"value"}
//static char jsonGenerics[][5] = {
//  "NULL",
//  "set",
//  "to",
//  "get"
//};



// 5. Finally Declare a structure that will hold both the jsonStates enum, and any data that will need to be passed from jsonMessenger, into the states.
// We can make this fairly generic by including additional datatypes, or we can reduce the size of the memory used by removing the unneeded ones
struct jsonStateData {
  jsonStates cmdState;  // The command state enum to tell state machine what state to go to next
  dataTypes data_type;  // The type of data being passed along with structure (though state should know what data to expect anyway), this could be removed to save space
  int16_t numeric;      // empty generic data slots for each data type
  float floatData;
  char msg[JSON_MSG_LENGTH];
  bool cmd_received;  // Flag set true by jsonLoop when cmd is received
};

//jsonStateData emptyStruct_example = { NONE, EMPTY, 0, 0.0, "", false };  // commented out as global var would eat up extra memory. Instead of using this variable, just copy the example into local scope where needed




#endif