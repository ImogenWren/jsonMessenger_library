/*  jsonMessenger State Machine Example

Written By:
Imogen Heard
32/01/2025



*/

/* Version Control 

Sketch uses 20000 bytes (62%) of program storage space. Maximum is 32256 bytes.
Global variables use 1649 bytes (80%) of dynamic memory, leaving 399 bytes for local variables. Maximum is 2048 bytes.


Sketch uses 20050 bytes (62%) of program storage space. Maximum is 32256 bytes.
Global variables use 1703 bytes (83%) of dynamic memory, leaving 345 bytes for local variables. Maximum is 2048 bytes.


*/




#include "globals.h"







void setup() {
  Serial.begin(115200);
  while (!Serial);
  // delay(2000);  // give time for Serial object to start
  //  std::cout << "\n{\"model\":\"" << EXPERIMENT_NAME << "\",\"version\":\"" << FIRMWARE_VERSION << "\",\"developed-by\":\"" << DEVELOPER << "\"}" << std::endl;
  Serial.print("\n{\"model\":\"");
  Serial.print(EXPERIMENT_NAME);
  Serial.print("\",\"version\":\"");
  Serial.print(FIRMWARE_VERSION);
  Serial.print("\",\"fw-developed-by\":\"");
  Serial.print(DEVELOPER);
  Serial.println("\"}");
  jsonRX.jsonBegin();  // Start the json library to accept commands over serial connection
}


void loop() {


  jsonStateData nextState_data = jsonRX.jsonReadSerialLoop();


  if (nextState_data.cmd_received) {  // If command is receive   //delay(10);



    const char* cmd = jsonRX.getCMDkey(nextState_data.cmdState);  // I feel like the entire point of using ENUMs is being totally lost by doing this, but it is working
    //std::cout << std::endl;
    // std::cout << "{\"rx-cmd\":\"" << cmd << "\",\"datatype\":\"" << jsonRX.getDataType(nextState_data.data_type) << "\",\"data\":\"";
    Serial.print("{\"rx-cmd\":\"");
    Serial.print(cmd);
    Serial.print("\",\"datatype\":\"");
    Serial.print(jsonRX.getDataType(nextState_data.data_type));
    Serial.print("\",\"data\":\"");
    if (nextState_data.data_type == INTEGER) Serial.print(nextState_data.numeric);  //std::cout << nextState_data.numeric;
    if (nextState_data.data_type == FLOAT) Serial.print(nextState_data.floatData);  //std::cout << nextState_data.floatData;
    if (nextState_data.data_type == CSTRING) Serial.print(nextState_data.msg);      //std::cout << nextState_data.msg;
    if (nextState_data.data_type == EMPTY) Serial.print("n/a");                     //std::cout << "n/a";
    // Is this now missing float clause?
    //std::cout << "\"}" << std::endl;
    Serial.println("\"}");

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
    } else if (nextState_data.cmdState == HELP) {
      smState = STATE_HELP;
    } else {
      // std::cout << "{\"WARNING\":\"Unrecognised cmdState\"}" << std::endl;
      Serial.println("{\"WARNING\":\"Unrecognised cmdState\"}");
    }
  }


  sm_Run(nextState_data);  // This Runs the state machine in the correct state, and is passed all of the data sent by the last command
  // NOTE System design question here, passing this value as a local variable means it cannot be updated elsewhere. Making it global means that other states would be able to modify the data
  // and pass it internally.
  // Skipping over this question, I am going to do the thing this would solve a different way
  // sm_Run();

  // Run Periodic Functions to gather data here


  if (streaming_active || snapshop_active) {
    if (sampleDelay.millisDelay(sampleDelay_mS)) {
      //print the sampled data
      update_json();
    }
    if (snapshop_active) {
      if (millis() - snapshot_starttime_mS >= snapshot_timer_mS) {
        snapshop_active = false;
      }
    }
  }

  errors.clear_warning();  // clear JSON (move this to bottom of loop later)
                           //  if (printDelay.millisDelay(20000)) {
                           // std::cout << "alive" << std::endl;
                           //Serial.println("Alive and Loop");
                           // display_mallinfo();
                           //  stepper.setRPM(0);
                           //}
}
