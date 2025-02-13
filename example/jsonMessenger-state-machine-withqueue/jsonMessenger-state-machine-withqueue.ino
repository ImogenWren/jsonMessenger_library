/*  jsonMessenger State Machine - With Queue Example

 Same as the other example contained in this library, however this version enables the queuing function for jsonMessenger

Written By:
Imogen Heard
32/01/2025



*/

/* Version Control 

V1.0.0 Without Queue
Sketch uses 15986 bytes (49%) of program storage space. Maximum is 32256 bytes.
Global variables use 986 bytes (48%) of dynamic memory, leaving 1062 bytes for local variables. Maximum is 2048 bytes.

V1.1.0 With Queue
Sketch uses 16666 bytes (51%) of program storage space. Maximum is 32256 bytes.
Global variables use 1257 bytes (61%) of dynamic memory, leaving 791 bytes for local variables. Maximum is 2048 bytes.


V1.1.0 Enabled State Machine debug
Sketch uses 17124 bytes (53%) of program storage space. Maximum is 32256 bytes.
Global variables use 1637 bytes (79%) of dynamic memory, leaving 411 bytes for local variables. Maximum is 2048 bytes.
???? 380 more bytes?!

V1.1.1 Fixed high memory useage due to loose strings in global
Sketch uses 18576 bytes (57%) of program storage space. Maximum is 32256 bytes.
Global variables use 1275 bytes (62%) of dynamic memory, leaving 773 bytes for local variables. Maximum is 2048 bytes.
- NEEDS TESTING

*/




#include "globals.h"







void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  // delay(2000);  // give time for Serial object to start
  //  std::cout << "\n{\"model\":\"" << EXPERIMENT_NAME << "\",\"version\":\"" << FIRMWARE_VERSION << "\",\"developed-by\":\"" << DEVELOPER << "\"}" << std::endl;
  Serial.print(F("\n{\"model\":\""));
  Serial.print(EXPERIMENT_NAME);
  Serial.print(F("\",\"version\":\""));
  Serial.print(FIRMWARE_VERSION);
  Serial.print(F("\",\"fw-developed-by\":\""));
  Serial.print(DEVELOPER);
  Serial.println(F("\"}"));
  jsonRX.jsonBegin();  // Start the json library to accept commands over serial connection
}


void loop() {

  // If using Queue function, then we dont need the data to be passed directly, we will use dequeue function instead
  // jsonStateData nextState_data = jsonRX.jsonReadSerialLoop();

  jsonRX.jsonReadSerialLoop();  // ReadSerialLoop is still called to enqueue commands

  jsonStateData nextState_data = { NONE, EMPTY, 0, 0.0, "", false };  //have to declare this outside of if statement?!
  // We only want to dequeue commands when the system is stable and ready to handle them. So we will wrap dequeue and only execute it while in STATE_WAIT
  if (smState == STATE_WAIT) {
    nextState_data = jsonRX.dequeue_cmd();
  }

  // The rest of the code can stay exactly the same as before
  if (nextState_data.cmd_received) {  // If command is received   //delay(10);



    const char* cmd = jsonRX.getCMDkey(nextState_data.cmdState);  // I feel like the entire point of using ENUMs is being totally lost by doing this, but it is working
    //std::cout << std::endl;
    // std::cout << "{\"rx-cmd\":\"" << cmd << "\",\"datatype\":\"" << jsonRX.getDataType(nextState_data.data_type) << "\",\"data\":\"";
    Serial.print(F("{\"rx-cmd\":\""));
    Serial.print(cmd);
    Serial.print(F("\",\"datatype\":\""));
    Serial.print(jsonRX.getDataType(nextState_data.data_type));
    Serial.print(F("\",\"data\":\""));
    if (nextState_data.data_type == INTEGER) Serial.print(nextState_data.numeric);  //std::cout << nextState_data.numeric;
    if (nextState_data.data_type == FLOAT) Serial.print(nextState_data.floatData);  //std::cout << nextState_data.floatData;
    if (nextState_data.data_type == CSTRING) Serial.print(nextState_data.msg);      //std::cout << nextState_data.msg;
    if (nextState_data.data_type == EMPTY) Serial.print(F("n/a"));                  //std::cout << "n/a";
    // Is this now missing float clause?
    //std::cout << "\"}" << std::endl;
    Serial.println(F("\"}"));

    // This is the bit that parses the command recieved by user, and sets the state machine to go to the correct state
    if (nextState_data.cmdState == STOP) {  // if fan speed change command received
      smState = STATE_STOP;
    } else if (nextState_data.cmdState == START) {
      smState = STATE_START;
    } else if (nextState_data.cmdState == SET_SPEED_HZ) {
      smState = STATE_SET_SPEED_HZ;
    } else if (nextState_data.cmdState == SET_SPEED_RPM) {
      smState = STATE_SET_SPEED_RPM;
    } else if (nextState_data.cmdState == HOME) {
      smState = STATE_HOME;
    } else if (nextState_data.cmdState == CALIBRATE) {
      smState = STATE_CALIBRATE;
    } else if (nextState_data.cmdState == FREEWHEEL) {
      smState = STATE_FREEWHEEL;
    } else if (nextState_data.cmdState == BRAKE) {
      smState = STATE_BRAKE;
    } else if (nextState_data.cmdState == GOTO) {
      smState = STATE_GOTO;
    } else if (nextState_data.cmdState == SAMPLERATE) {
      smState = STATE_SAMPLERATE;
    } else if (nextState_data.cmdState == STARTSTREAM) {
      smState = STATE_STARTSTREAM;
    } else if (nextState_data.cmdState == STOPSTREAM) {
      smState = STATE_STOPSTREAM;
    } else if (nextState_data.cmdState == SNAPSHOT) {
      smState = STATE_SNAPSHOT;
    } else if (nextState_data.cmdState == SNAPTIME) {
      smState = STATE_SNAPTIME;
    } else if (nextState_data.cmdState == PING) {
      smState = STATE_PING;
    } else if (nextState_data.cmdState == STATUS) {
      smState = STATE_STATUS;
    } else if (nextState_data.cmdState == HELP) {
      smState = STATE_HELP;
    } else {
      // std::cout << "{\"WARNING\":\"Unrecognised cmdState\"}" << std::endl;
      Serial.println(F("{\"WARNING\":\"Unrecognised cmdState\"}"));
    }
  }

  //TODO Can this data be passed as a pointer to save some overheads?

  sm_Run(&nextState_data);  // This Runs the state machine in the correct state, and is passed all of the data sent by the last command
  // NOTE System design question here, passing this value as a local variable means it cannot be updated elsewhere. Making it global means that other states would be able to modify the data
  // and pass it internally.


  // Run Periodic Functions to gather data here


  if (streaming_active || snapshop_active) {
    if (sampleDelay.millisDelay(sampleDelay_mS)) {
      //print the sampled data
      //update_json();
      //  errors.print_json_status(true);
    }
    if (snapshop_active) {
      if (millis() - snapshot_starttime_mS >= snapshot_timer_mS) {
        snapshop_active = false;
      }
    }
  }

  errors.clear_warning();
}
