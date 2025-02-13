/* errorConfig.h

Ideas for improvements to the error reporting system


*/


// Define list of enums here for error codes


/*
  typedef enum {
    ETH_CABLE_DISCONNECT = -3,
    I2C_ERROR = -7,
    WATCHDOG_TIMER_EXP = -8,
    TEMP_OUTOF_RANGE = -9,
    OUT_OF_RANGE_VAL = -10
  } errorCode;


struct errorCodeStruct = {
  int errorCode;
  messageLevel errorLevel;
}

// Better, list of structs


*/

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