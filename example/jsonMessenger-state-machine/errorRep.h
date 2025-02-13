/* errorRep.h Error Reporting and Management System

Imogen Heard
11/02/2025

*/

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
//#include <stdint.h>

//#include "globals.h"


/*        Template for Error Codes
-2       
-3       Ethernet Cable Likely disconnected                   FATAL
-4       
-5       
-6       
-7      I2C Error                                             FATAL
-8      watchdog timer expired                                WARNING
-9      Temperature Out of Range Detected                     WARNING
-10     Out of Range Value commanded                          WARNING
-11     
-12     
-13     
-14     
-15     
-16     
-17     ESTOP button Pressed                                  FATAL
-18
-19
-20     Unknown JSON command Recieved                         ERROR
-21     Exception in State Machine                            ERROR

*/




#define JSON_BUFFER_SIZE 150  // used to print error report -> make sure sized to print all error data when requested

#define ERROR_MSG_LENGTH 24  // Increase for more verbose error messages, decrease to save memory
#define CONTEXT_LENGTH 24    //  Increase for verbose context descriptions, decrease to save memory

#define DEBUG_ERRORS false
#define ERROR_LEVEL_PRIORITY_ENABLE false
#define WARNING_ACTIVE_PERIOD_mS 60000  // 1 min


class errorRep {
public:
  // Constructor
  errorRep();

  // Logging Level Constants
  typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
  } messageLevel;



  const char debugLevel[5][8] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
  };




  struct errorStatus {
    bool ok;
    int16_t code;
    char msg[ERROR_MSG_LENGTH];
    messageLevel level;
    char context[CONTEXT_LENGTH];
    uint32_t logtime;
  };

  errorStatus currentStatus = { true, 0, "", INFO, "" };

  void print_json_status(bool printPretty = false);
  int get_message_level(const char* message_level);
  void set_error(bool ok = true, int16_t code = 0, const char* msg = "", messageLevel logLevel = INFO, const char* context = "");
  void hard_set_error(bool ok = true, int16_t code = 0, const char* msg = "", messageLevel logLevel = INFO, const char* context = "");
  void clear_error(int16_t error_code, bool clear_fatal = false);
  // This function should be called periodically to clear errors with message level "WARNING"
  void clear_warning();


  bool FATAL_ERROR = false;
  int16_t FATAL_ERROR_CODE = 0;


private:


  int16_t last_warning_code = 0;
  uint32_t warning_set_time_mS;
};
