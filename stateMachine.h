/*

#pragma once

#ifndef stateMachine_h
#define stateMachine_h

#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager] #NOTE: Version 7.x.x uses dynamic memory allocation and should be avoided if possible


//# JSON Varibles & Object Declaration
// These variables relate to incoming serial commands & parsing it
#define COMMAND_SIZE 48                // was 64 reduced to save space
StaticJsonDocument<COMMAND_SIZE> doc;  // This is the JSON object


#if COMMAND_HINTS == true
char exampleCommands[][32] = {
  "{\"mode\":\"stop\"}",
  "{\"set\":\"mode\",\"to\":\"stop\"}",
  "{\"heater\":0}",
  "{\"heater\":1}",
  "{\"set\":\"heater\",\"val\":0}",
  "{\"flow\":0}",
  "{\"flow\":50}",
  "{\"set\":\"flow\",\"value\":75}",
};
#endif

/** State Machine Global Variables
 * Defines the valid states for the state machine
 * 
 */

 /*
typedef enum {
  STATE_INIT,
  STATE_WAIT,
  STATE_STOP,
  STATE_START_HEATER,
  STATE_STOP_HEATER,
  STATE_FLOW_VALVE,
  STATE_STOP_FLOW
} StateType;

/**
 * Stores the current state of the state machine
 */

 /*
StateType smState = STATE_INIT;
StateType lastState;

// State Names Array (Makes printing the current state prettier)
char stateNames[][20] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_START_HEATER",
  "STATE_STOP_HEATER",
  "STATE_FLOW_VALVE"
  "STATE_STOP_FLOW"
};

//state Machine function prototypes
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_start_heater(void);
void sm_state_stop_heater(void);
void sm_state_flow_valve(void);
void sm_state_stop_flow(void);
int NUM_STATES = 7;


// Intent to create a common data structure to be passed between JSON parser & state machine functions./
// Holds both the new state for the state machine, and any possible data that needs to be sent to the state
// Unused values can remain empty
struct stateMachine {
  StateType state;
  int numeric;
  float data;
  char msg[16];
  bool ok;
};


/*
 
 Commands I want to be able to parse

 {A1:}


*/

/*
typedef enum {
  A0,
  A1,
  A2,
  A3,
  A4,
  B0,
  B1,
  B2,
  B3,
  B4,
  C0,
  C1,
  C2,
  C3,
  C4
} bankA;

char bankA_names[][3] = {
  "A0", "A1", "A2", "A3", "A4",
  "B0", "B1", "B2", "B3", "B4",
  "C0", "C1", "C2", "C3", "C4"
};

typedef enum {
  D0,
  D1,
  D2,
  D3,
  D4,
  E0,
  E1,
  E2,
  E3,
  E4
} bankB;

#define PRETTY_PRINT_JSON true



void check_for_fan_cmnd(const char *key) {
  for (int i = 0; i < 15; i++) {
    if (strcmp(key, bankA_names[i]) == 0) {
      Serial.print("Key Found:");
      Serial.print(key);
      Serial.print(" at positon: ");
      Serial.println(i)
    }
  }
}


void check_for_key(const char *key, ) {
  for (int i = 0; i < 15; i++) {
    if (strcmp(key, bankA_names[i]) == 0) {
      Serial.print("Key Found:");
      Serial.print(key);
      Serial.print(" at positon: ");
      Serial.println(i)
    }
  }
}


stateMachine parse_json(const char *key) {}


int readSerialJSON(void) {

  bool commandParsed = false;
  int error = 0;
  char command[COMMAND_SIZE];

  if (Serial.available() > 0) {

    Serial.readBytesUntil(10, command, COMMAND_SIZE);
#if DEBUG_SERIAL == true
    Serial.print(F("\ncommand received: "));
    Serial.println(command);
#endif

    printJSON(command);

    deserializeJson(doc, command);
    JsonObject root = doc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"
  }
}












#endif

*/