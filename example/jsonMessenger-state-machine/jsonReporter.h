/*  jsonReporter.h

 Functions to load data into a json template and print to Serial Output

*/




#include "globals.h"



void update_json() {
  //freeRAM = ram.getPrintStats("update_json");
  // Header
  jsonTX[F("timestamp")].set(millis());  //Message Timestamp set this last before printing
                                         // Payload
  jsonTX[F("payload")][F("state")].set(stateNames[smState]);
  // Output Data
  // Stepper Motor Settings
  jsonTX[F("payload")][F("step")][F("hz")].set(-2);
  jsonTX[F("payload")][F("step")][F("rpm")].set(-1);
  // Encoder Data

  jsonTX[F("payload")][F("encode")][F("hz")].set(0);
  jsonTX[F("payload")][F("encode")][F("rpm")].set(1);
  jsonTX[F("payload")][F("encode")][F("pos(raw)")].set(2);
  jsonTX[F("payload")][F("encode")][F("pos")].set(3);

  // MPU Data
  jsonTX[F("payload")][F("mpu")][F("acc")][F("x")].set(4);
  jsonTX[F("payload")][F("mpu")][F("acc")][F("y")].set(5);
  jsonTX[F("payload")][F("mpu")][F("acc")][F("z")].set(6);
  jsonTX[F("payload")][F("mpu")][F("gyro")][F("x")].set(7);
  jsonTX[F("payload")][F("mpu")][F("gyro")][F("y")].set(8);
  jsonTX[F("payload")][F("mpu")][F("gyro")][F("z")].set(9);

  // Meta Data & Debugging
  //jsonTX[F("meta")][F("sizeof")].set(sizeof(jsonTX));


  // int JSON_bytes = sizeof(jsonTX);  // used for debugging
  //Serial.print("Size of JSON: ");
  //Serial.println(JSON_bytes);

  if (PRINT_JSON) {
#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
    serializeJsonPretty(jsonTX, Serial);
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
    serializeJson(jsonTX, Serial);
#endif
    Serial.print(F("\n"));
  }
}