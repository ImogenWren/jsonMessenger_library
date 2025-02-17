#include "errorRep.h"



// Constructor
errorRep::errorRep() {

  
}



void errorRep::print_json_status(bool printPretty) {
  StaticJsonDocument<JSON_BUFFER_SIZE> JSONstatus;


  JSONstatus[F("level")].set(debugLevel[currentStatus.level]);
  JSONstatus[F("context")].set(currentStatus.context);
  JSONstatus[F("payload")][F("status")][F("ok")].set(currentStatus.ok);
  JSONstatus[F("payload")][F("status")][F("code")].set(currentStatus.code);
  JSONstatus[F("payload")][F("status")][F("msg")].set(currentStatus.msg);
  JSONstatus[F("payload")][F("status")][F("logtime")].set(currentStatus.logtime);

  if (printPretty) {
    serializeJsonPretty(JSONstatus, Serial);
  } else {
    serializeJson(JSONstatus, Serial);
  }
  Serial.print(F("\n"));
}




// returns level of the message or -1 if error in lookup
// Refactoring this code made this function pretty useless
/*
int errorRep::get_message_level(const char* message_level) {
  return currentStatus.level;
}
*/
/*
for (int i = 0; i < 5; i++) {
    if (!strcmp(debugLevel[i], message_level)) {
      return i;
    }
  }
  return -1;
*/



// Use this to set errors elsewhere, can also be used to reset errors by calling with no arguments
void errorRep::set_error(bool ok, int16_t code, const char* msg, messageLevel logLevel, const char* context) {
#if ERROR_LEVEL_PRIORITY_ENABLE == true
  //  int16_t current_error_level = get_message_level(JSON["level"]);  // Get current error level
  messageLevel current_error_level = currentStatus.level;
  if (logLevel >= current_error_level) {
#endif
    hard_set_error(ok, code, msg, logLevel, context);
    if (logLevel == FATAL) {
      FATAL_ERROR = true;       //
      FATAL_ERROR_CODE = code;  // log the error that caused the FATA_ERROR as can be cleared later if required
    }
#if DEBUG_ERRORS == true
    Serial.print(F("DEBUG_ERRORS (set): "));
    Serial.print(code);
    Serial.print(F("  msg: "));
    Serial.println(msg);
#endif
#if ERROR_LEVEL_PRIORITY_ENABLE == true
  } else {
    // New Error was lower level than previous error so ignore
    // Do nothing
  }
#endif
}


/*


*/


// Same as set error, but always ignores priority
void errorRep::hard_set_error(bool ok, int16_t code, const char* msg, messageLevel logLevel, const char* context) {
  currentStatus.ok = ok;
  currentStatus.code = code;
  strcpy(currentStatus.msg, msg);
  currentStatus.level = logLevel;
  strcpy(currentStatus.context, context);
  currentStatus.logtime = uint32_t(millis() / 1000);
  if (logLevel == FATAL) {
    FATAL_ERROR = true;       //
    FATAL_ERROR_CODE = code;  // log the error that caused the FATA_ERROR as can be cleared later if required
  }
}




void errorRep::clear_error(int16_t error_code, bool clear_fatal) {
  // int16_t current_error = JSONstatus[F("payload")][F("status")][F("code")];
  messageLevel current_error_level = currentStatus.level;
#if DEBUG_ERRORS == true
  Serial.print(F("DEBUG_ERRORS (clear): current_error: "));
  Serial.print(current_error);
  Serial.print(F(" clear_code: "));
  Serial.println(error_code);
#endif
  if (currentStatus.code == error_code) {
    hard_set_error();  // Set error with no values passed clears the current error
    if (clear_fatal) {
      if (FATAL_ERROR_CODE == error_code) {  // This may lead to confusion if multiple fatal errors ave occured, may need simplifying later
        FATAL_ERROR_CODE = 0;
        FATAL_ERROR = false;
      }
    }
#if DEBUG_ERRORS == true
    Serial.println(F("Errors Mached & Deleted"));
#endif
  }
}




// This function should be called periodically to clear errors with message level "WARNING"
void errorRep::clear_warning() {
  bool error_status = currentStatus.ok;  //JSONstatus[F("payload")][F("status")][F("ok")];

  if (!error_status) {                                 // if any error has been triggered (false bool)
                                                       // Get the error code
    int16_t active_warning_code = currentStatus.code;  //JSONstatus[F("payload")][F("status")][F("code")];
    // Check the level of the error
    // char msg_level[8];
    //  A string copy HERE JSON["level"] into msg_level
    /// strcpy(msg_level, JSONstatus[F("level")]);
    messageLevel current_error_level = currentStatus.level;

#if DEBUG_ERRORS == true
    Serial.print(F("Debug Errors: Error Found: "));
    Serial.print(active_warning_code);
    Serial.print(F(", "));
    Serial.println(msg_level);
#endif

    // if (!strcmp(msg_level, debugLevel[WARNING])) {  // returns 0 if strings match
    if (current_error_level == WARNING) {
      if (active_warning_code != last_warning_code) {
        warning_set_time_mS = millis();  // save the time the warning was set
        last_warning_code = active_warning_code;
      } else {  // If active warning is true, start checking time
        if (millis() - warning_set_time_mS >= WARNING_ACTIVE_PERIOD_mS) {
          clear_error(active_warning_code, false);
          last_warning_code = 0;
        }
      }
    }
  }
}