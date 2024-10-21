# jsonMessenger_library
 Library for easy configuration of a JSON based Serial messaging system for Arduino

_This library has been developed to simplify the implementation of transfer of control data from a user interface, over Serial connections to embedded projects running state machines._

It works by associating different keywords used to define commands sent by a user or user interface, with a list of known states, that could represent all, or some of the various states of a state machine, and 
a list of the expected variable types to be sent along with the defined keywords.



 ## Use
 _This library is configured for different users entirely within the `jsonConfig.h` file._

### Modifying jsonConfig.h
 1. Define an enum to define variable types, These will be linked to a state enum so when a message with a keyword is received, we can look up what 
 data type will be included with the message
 ```
typedef enum {  // enum to pass variable types between functions
  EMPTY,
  INTEGER,
  FLOAT,
  CHAR_ARRAY
} dataTypes;
```

1b. Define char string for the above enum to allow us to print out the enum above in a human readable format!
```
static char typeNames[][12] = {
  "EMPTY",
  "INTEGER",
  "FLOAT",
  "CHAR_ARRAY"
};
```

2. Declare a list of all possible key values as ENUM. These values will be passed out of the jsonMessenger Object and can be used to control
a state machine seperate from this library.
_NOTE this list may not include all possible states, JUST the states that are triggered by receiving a command, including a null value at 0_

```
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
```

2b. Then Declare a list of key commands that will be required to be parsed. This must match the order of the enums above, including the NULL or
NONE value, but does not have to include NUM_VALUES. This list will be the actual commands that can be parsed by the system
```
static char jsonCommandKeys[][5] = {
  "none",
  "A0", "A1", "A2", "A3", "A4",
  "B0", "B1", "B2", "B3", "B4",
  "C0", "C1", "C2", "C3", "C4",
  "D0", "D1", "D2", "D3", "D4",
  "E0", "E1", "E2", "E3", "E4",
  "all", "mod", "usr"
};
```
NOTE, this can also be used to turn the enums above back into strings for human readability, though this list is memory intensive and should 
not be copied outside of this library. Instead use functions within the library to print the values to the user if required.




3. Now Link each jsonState ENUM with the datatype ENUM in a map structure.
//In this example most will be integers, but will include some cstrings and to test.
```
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
```

4. Finally Declare a structure that will hold both the jsonStates enum, and any data that will need to be passed from jsonMessenger and outside of 
this library. <br>

We can make this fairly generic by including additional datatypes, or we can reduce the size of the memory used by removing the unneeded ones. <br>
This structure must include the jsonState, dataType and a `command_received` bool that can be used to flag that a new command has been received to methods 
outside of the library. All other data is arbitary and will depend on use case, though the library has been built to accomidate those listed. 
```
struct jsonStateData {
  jsonStates cmdState;        // The command state enum to tell state machine what state to go to next
  dataTypes data_type;        // The type of data being passed along with structure (though state should know what data to expect anyway), this could be removed to save space
  int numeric;                // empty generic data slots for each data type
  float data;
  char msg[16];
  bool cmd_received;           // Flag set true by jsonLoop when cmd is received
};
```

<br><br>

With these program structures filled in for the specific use case, we can look at the program outside of the library and how it can be used!




