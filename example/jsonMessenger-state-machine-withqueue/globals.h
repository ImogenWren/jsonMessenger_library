/*  globals.h
      Define all user set values, global constants, global vars, included libraries and global objects

      Imogen Heard
      25/01/2025
*/

#pragma once

// Add included external libraries here (at the top of globals.h)
//#include <iostream>
//#include <stdlib.h>
#include <autoDelay.h>    // https://github.com/PanGalacticTech/autoDelay_library
#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager]

// Add included internal libraries here (Top of globals.h, underneath external libraries)
#include "errorRep.h"
#include "jsonMessenger.h"


// Program Attributes
#define EXPERIMENT_NAME "jsonMessenger-state-machine-with-queue"
#define FIRMWARE_VERSION "V0.0.0"
#define DEVELOPER "Imogen-Wren"

// Hardware Definitions

// User Options & program config


// Error System
#define WARNING_ACTIVE_PERIOD_mS 60000  // 1 min

// JSON Options
// jsonMessenger    -> send and parse commands
#define COMMAND_SIZE 64  // what command find better description

// jsonReporter     -> report data
#define PRINT_RATE_Hz 40
#define PRINT_PERIODIC_UPDATES true
#define PRINT_JSON true
#define PRETTY_PRINT_JSON false


// Debugging Options
#define DEBUG_STATES false
#define DEBUG_STATE_MACHINE true
#define COMMAND_HINTS false



// Dummy Vals
#define MAX_HZ 100
#define MAX_RPM 400


// Create objects
jsonMessenger jsonRX;  // create a jsonMessenger object to handle commands received over Serial connection
autoDelay printDelay;  // Delay object for printing periodic JSON messages // DEPRECIATED FOR NOW
errorRep errors;

autoDelay sampleDelay;
uint16_t sampleRate_Hz = 1;
uint32_t sampleDelay_mS = 1000 / sampleRate_Hz;

// Global Variables


// Sampling Vars
bool streaming_active = false;
bool snapshop_active = false;
uint16_t snapshot_timer_mS = 25000;
uint32_t snapshot_starttime_mS;

uint32_t print_delay_mS = 1000 / PRINT_RATE_Hz;





// Add included internal header files here (at the bottom of globals.h)
#include "stateConfig.h"
#include "jsonReporter.h"

