/*  stateConfig.h

This header defines the state machine framework. It is intended to be used with the jsonMessenger.h Library to handle receiving and parsing JSON formatted commands entered by a user, 
however this state machine also operates independently and can be used without jsonMessenger.h

This State Machine framework can be adapted to many different purposes, follow the numbered comments for an explanation

Imogen Heard
11/02/2025


*/

#pragma once

#include "globals.h"


// 1. Define all the valid states for the state machine with an enum.
//    - This should include states triggered by user input, but may also contain states that are only accessable programatically
typedef enum {
  STATE_INIT,
  STATE_WAIT,
  STATE_STOP,
  STATE_START,
  STATE_SET_SPEED_HZ,
  STATE_SET_SPEED_RPM,
  STATE_HOME,
  STATE_CALIBRATE,
  STATE_FREEWHEEL,
  STATE_BRAKE,
  STATE_GOTO,
  STATE_SAMPLERATE,
  STATE_STARTSTREAM,
  STATE_STOPSTREAM,
  STATE_SNAPSHOT,
  STATE_SNAPTIME,
  STATE_PING,
  STATE_HELP,
  NUM_STATES  // Sentinal value lets us get the total number of states without manually counting. Do not forget this value, it is important for correct function
} StateType;


// 2. Then we define two variables to hold the current state enum, and the previous state enum. Holding both these values allows us to compare them as we enter a state,
//    to see if it is the first time we have entered the state.

StateType smState = STATE_INIT;
StateType lastState;




// 3. Define a State Names Array, this will allow us to print the enum above in human readable format
char stateNames[][20] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_START",
  "STATE_SET_SPEED_HZ",
  "STATE_SET_SPEED_RPM",
  "STATE_HOME",
  "STATE_CALIBRATE",
  "STATE_FREEWHEEL",
  "STATE_BRAKE",
  "STATE_GOTO",
  "STATE_SAMPLERATE",
  "STATE_STARTSTREAM",
  "STATE_STOPSTREAM",
  "STATE_SNAPSHOT",
  "STATE_SNAPTIME",
  "STATE_PING",
  "STATE_HELP"
};


// 4. Define the state machine function prototypes.
//    Any function that will be passed data from a user input will be passed the same jsonStateData structure as an argument.
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_start(void);
void sm_state_set_speed_hz(jsonStateData stateData);
void sm_state_set_speed_rpm(jsonStateData stateData);
void sm_state_home(void);
void sm_state_calibrate(void);
void sm_state_freewheel(void);
void sm_state_brake(void);
void sm_state_goto(jsonStateData stateData);
void sm_state_samplerate(jsonStateData stateData);
void sm_state_start_stream(jsonStateData stateData);
void sm_state_stop_stream(void);
void sm_state_snapshot(void);
void sm_state_snaptime(jsonStateData stateData);
void sm_state_ping(void);
void sm_state_help(void);





// 5. Define all the state machine functions
//    - A typical state function template is shown below

/*
void sm_state_template(jsonStateData stateData) {
  if (lastState != smState) {  // Check to see if first time state has been called in sequence
    // 5a. Do anything that needs to happen the First time this state is called
    lastState = smState;  // Set the last state to the current state
  }
  // 5b. Do everything that repeats as long as this state is active

  // 5c. Extract data from jsonStateData (if required)
          - remember to validate data if coming from user input!

  if (stateData.numeric < 1 || stateData.numeric > 2000){
    // Error message to user if data is out of accepted bounds
  } else {
    // accept the data and process
  }

  // 5d. Add any logic to navigate to other states
  smState = STATE_WAIT;
}
*/

#define STATE_INIT_TEXT 'state: init'

// Init state, only called at startup
void sm_state_init() {
  if (lastState != smState) {
    Serial.println(STATE_INIT_TEXT);
  }

  smState = STATE_WAIT;
}


// Doing this doesnt actually save any RAM compared to having F macro strings within a function. 
const char cmd_0[] PROGMEM = "{\"start\":0}           -> Start/Update Motor Speed";
const char cmd_1[] PROGMEM = "{\"stop\":0}            -> Stop Motor";
const char cmd_2[] PROGMEM = "{\"hz\": -20 to 20}     -> Set Motor Speed in Hz";
const char cmd_3[] PROGMEM = "{\"rpm\": -200 to 200}  -> Set Motor Speed in RPM";
const char cmd_4[] PROGMEM = "{\"home\":}             -> Move Motor to home pos";
const char cmd_5[] PROGMEM = "{\"cal\":}              -> Run Calibration to home motor";
const char cmd_6[] PROGMEM = "{\"free\":}             -> Set freewheel brake mode (test)";
const char cmd_7[] PROGMEM = "{\"brake\":}            -> Set coolbrake brake mode (test)";
const char cmd_8[] PROGMEM = "{\"goto\": -360 to 360} -> Goto Angle (test)";
const char cmd_9[] PROGMEM = "{\"sample\": 1 to 40}   -> Set Samplerate in Hz";
const char cmd_10[] PROGMEM = "{\"stream\":}           -> Start Data Streaming";
const char cmd_11[] PROGMEM = "{\"endst\":}            -> End Data Streaming";
const char cmd_12[] PROGMEM = "{\"snap\":}             -> Take Data Snapshot";
const char cmd_13[] PROGMEM = "{\"time\": 1 - 250000 } -> Set Time for Data Snapshot (mS)";
const char cmd_14[] PROGMEM = "{\"ping\":}             -> Ping Servo";
const char cmd_15[] PROGMEM = "{\"help\":}             -> Print Commands to Serial Monitor";

#define LONGEST_STRING 59
#define LIST_LENGTH 16

const char *const cmd_table[] PROGMEM = {
  cmd_0,
  cmd_1,
  cmd_2,
  cmd_3,
  cmd_4,
  cmd_5,
  cmd_6,
  cmd_7,
  cmd_8,
  cmd_9,
  cmd_10,
  cmd_11,
  cmd_12,
  cmd_13,
  cmd_14,
  cmd_15
};


//https://forum.arduino.cc/t/using-large-text/248390/7
// Not a state, but function called by "help" state to print commands list to users
void print_cmds() {
  char buffer[LONGEST_STRING + 1];
  for (int i = 0; i < LIST_LENGTH; i++) {
    strcpy_P(buffer, (char *)pgm_read_ptr(&(cmd_table[i])));  // Necessary casts and dereferencing, just copy.
    Serial.println(buffer);
  }
}
/*
  Serial.println(F("   {\"start\":0}          -> Start/Update Motor Speed"));
  Serial.println(F("   {\"stop\":0}           -> Stop Motor              "));
  Serial.println(F("   {\"hz\": -20 to 20}    -> Set Motor Speed in Hz   "));
  Serial.println(F("   {\"rpm\": -200 to 200} -> Set Motor Speed in RPM  "));
  Serial.println(F("   {\"home\":\"\"}        -> Move Motor to home pos (test) "));
  Serial.println(F("   {\"cal\":\"\"}         -> Run Calibration to home motor "));
  Serial.println(F("   {\"free\":\"\"}        -> Set freewheel brake mode (test)"));
  Serial.println(F("   {\"brake\":\"\"}       -> Set coolbrake brake mode (test)"));
  Serial.println(F("   {\"goto\": -360 to 360}-> Goto Angle (test)              "));
  Serial.println(F("   {\"sample\": 1 to 40}  -> Set Samplerate in Hz         "));
  Serial.println(F("   {\"stream\":\"\"}      -> Start Data Streaming    "));
  Serial.println(F("   {\"endst\":\"\"}       -> End Data Streaming      "));
  Serial.println(F("   {\"snap\":\"\"}        -> Take Data Snapshot       "));             // Take a Snapshot of data
  Serial.println(F("   {\"time\": 1 - 250000 }-> Set Time for Data Snapshot (mS)  "));     // Change the time over which the data snapshot is taken
  Serial.println(F("   {\"ping\":\"\"}        -> Ping Servo               "));             // Ping the wobble-shaft with the servo
  Serial.println(F("   {\"help\":\"\"}        -> Print Commands to Serial Monitor    "));  // Print commands list

}
*/

// State Wait is the default state for this program
void sm_state_wait() {
  if (lastState != smState) {
    // If first iteration print state machine status
#if DEBUG_STATES == true
    Serial.println(F("state: WAIT"));
#endif

#if COMMAND_HINTS == true  // print suggested commands
    Serial.println(F("\nEnter cmd in format:"));
    print_cmds();
#endif
    lastState = smState;
  }
}



// Stop the Motor
void sm_state_stop(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: STOP"));
#endif
    lastState = smState;
  }

  smState = STATE_STOPSTREAM;
}


// Start the Motor / Update entered speed in Hz or RPM to output
void sm_state_start(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: START"));
#endif
    lastState = smState;
  }
  smState = STATE_STARTSTREAM;
}





// Set the Motor Speed in Hz
void sm_state_set_speed_hz(jsonStateData stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_SPEED_HZ"));
#endif
    lastState = smState;
  }
  if (stateData.floatData < (-1 * MAX_HZ) || stateData.floatData > MAX_HZ) {  // if value is out of range, reject
    errors.set_error(false, -10, 'Requested Hz value out of bounds', errors.WARNING, "set_speed_hz");
    errors.print_json_status(true);
  } else {
    Serial.print(F("{\"hz-set-to\":\""));
    Serial.print(stateData.floatData);
    Serial.println(F("\"}"));
  }
  smState = STATE_WAIT;
}


// Set the Motor Speed in RPM
void sm_state_set_speed_rpm(jsonStateData stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_SPEED_RPM"));
#endif
    lastState = smState;
  }
  if (stateData.floatData < (-1 * MAX_RPM) || stateData.floatData > MAX_RPM) {  // if value is out of range, reject
    errors.set_error(false, -10, "Requested RPM value out of bounds", errors.WARNING, "set_speed_rpm");
    errors.print_json_status(true);
  } else {
    Serial.print("{\"rpm-set-to\":\"");
    Serial.print(stateData.floatData);
    Serial.println("\"}");
  }
  smState = STATE_WAIT;
}






// Send motor to home position (without recalibrating -> not particularly accurate)
void sm_state_home(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: HOME"));
#endif
    lastState = smState;
  }
  smState = STATE_WAIT;
}


// Run motor home position calibration and homing scripts
void sm_state_calibrate(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: CALIBRATE"));
#endif
    lastState = smState;
  }

  smState = STATE_WAIT;
}







// Set brake mode to freewheel (does not stop the motor or enter brake mode -> Still trying to figure out how to enter brake mode)
void sm_state_freewheel(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: FREEWHEEL"));
#endif
    lastState = smState;
  }

  smState = STATE_WAIT;
}


// Set brake mode to COOLBRAKE (adds resistance above FREEWHEEL by shorting H-Bridge driver, but does not apply current to oppose motion)
void sm_state_brake(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: BRAKE"));
#endif
    lastState = smState;
  }

  smState = STATE_WAIT;
}







// Go to absolute angle (somewhat accurate if recently calibrated -> may take several rotations to find position)
void sm_state_goto(jsonStateData stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: GOTO"));
#endif
    lastState = smState;
  }

  smState = STATE_WAIT;
}









// Change the samplerate of streamed or snapshotted data (Init at 10 Hz)
void sm_state_samplerate(jsonStateData stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SAMPLERATE"));
#endif
    lastState = smState;
  }
  if (stateData.numeric < 1 || stateData.numeric > 40) {
    errors.set_error(false, -10, "Out of Bounds Sample Rate Commanded", errors.WARNING, "state-samplerate");
    errors.print_json_status();
  } else {
    sampleRate_Hz = stateData.numeric;
    sampleDelay_mS = 1000 / sampleRate_Hz;
  }
  smState = STATE_WAIT;
}


// Start streaming data
void sm_state_start_stream() {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: STARTSTREAM"));
#endif
    lastState = smState;
  }
  streaming_active = true;
  smState = STATE_WAIT;
}



// Stop streaming data
void sm_state_stop_stream(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: STOPSTREAM"));
#endif
    lastState = smState;
  }
  streaming_active = false;
  smState = STATE_WAIT;
}


// Trigger a snapshot of data to be taken over X amount of time
void sm_state_snapshot() {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SNAPSHOT"));
#endif
    lastState = smState;
  }
  snapshop_active = true;
  snapshot_starttime_mS = millis();
  smState = STATE_WAIT;
}


// Set the period over which snapshot data is recorded (init to 25 seconds)
void sm_state_snaptime(jsonStateData stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SNAPTIME"));
#endif
    lastState = smState;
  }
  if (stateData.numeric < 1 || stateData.numeric > 250000) {
    errors.set_error(false, -10, "Out of Bounds Snapshot Time Commanded", errors.WARNING, "state-snaptime");
    errors.print_json_status();
  } else {
    snapshot_timer_mS = stateData.numeric;
  }
  smState = STATE_WAIT;
}


// Trigger the servo to "ping" the wobble bar for observation of natural decay.
//  Note -> this state also transitions to snapshot state to aid data capture of the event.
//          - This behaviour can be changed if required.
void sm_state_ping(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SAVE"));
#endif
    lastState = smState;
  }
  smState = STATE_SNAPSHOT;
}



// Print the commands list to the Serial Output
void sm_state_help(void) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: help"));
#endif
    lastState = smState;
  }
  print_cmds();
  smState = STATE_WAIT;
}




// 6. Finally define the state machine function
//    - Automatically generate the switch case from the list of ENUM states and list of functions! -> https://github.com/ImogenWren/switch-case-generator
void sm_Run(jsonStateData stateData) {
  if (smState < NUM_STATES) {
#if DEBUG_STATE_MACHINE == true
    if (lastState != smState) {
      Serial.print(F("{\"statemachine\":\""));
      Serial.print(stateNames[smState]);
      Serial.println(F("\"}"));
    }
#endif
    switch (smState) {
      case STATE_INIT:
        sm_state_init();
        break;
      case STATE_WAIT:
        sm_state_wait();
        break;
      case STATE_STOP:
        sm_state_stop();
        break;
      case STATE_START:
        sm_state_start();
        break;
      case STATE_SET_SPEED_HZ:
        sm_state_set_speed_hz(stateData);
        break;
      case STATE_SET_SPEED_RPM:
        sm_state_set_speed_rpm(stateData);
        break;
      case STATE_HOME:
        sm_state_home();
        break;
      case STATE_CALIBRATE:
        sm_state_calibrate();
        break;
      case STATE_FREEWHEEL:
        sm_state_freewheel();
        break;
      case STATE_BRAKE:
        sm_state_brake();
        break;
      case STATE_GOTO:
        sm_state_goto(stateData);
        break;
      case STATE_SAMPLERATE:
        sm_state_samplerate(stateData);
        break;
      case STATE_STARTSTREAM:
        sm_state_start_stream();
        break;
      case STATE_STOPSTREAM:
        sm_state_stop_stream();
        break;
      case STATE_PING:
        sm_state_ping();
        break;
      case STATE_HELP:
        sm_state_help();
        break;
      case STATE_SNAPSHOT:
        sm_state_snapshot();
        break;
      case STATE_SNAPTIME:
        sm_state_snaptime(stateData);
        break;
      default:
        sm_state_stop();
        Serial.println(F("sm: Exception -> default"));
        break;
    }
  } else {
    sm_state_stop();
    Serial.println(F("sm: Exception -> NUM_STATES exceeded"));
  }
}
