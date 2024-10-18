

#include "jsonMessenger.h"


jsonMessenger::jsonMessenger() {
}


void jsonMessenger::jsonBegin() {
  Serial.begin(115200);
  Serial.println("{\"json\":\"Messenger\", \"version\":\"V0.0.0\"}");
}




void jsonMessenger::printJSON() {
#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
  serializeJsonPretty(jsonRXdoc, Serial);
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
  serializeJson(jsonRXdoc, Serial);
#endif
  Serial.print(F("\n"));
}





jsonStateData jsonMessenger::jsonReadSerialLoop() {
  bool commandParsed = false;
  int error = 0;
  char command[JSON_RX_SIZE];
  jsonStateData jsonRX_data = { NONE, EMPTY, 0, 0, "", false };

  if (Serial.available() > 0) {
    Serial.readBytesUntil(10, command, JSON_RX_SIZE);
    Serial.print(F("\ncommand received: "));
    Serial.println(command);


    deserializeJson(jsonRXdoc, command);
    JsonObject root = jsonRXdoc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"
    // Now to parse the JSON message
    // First get number of elements in the jsonStates enum
    //int numValues = NUM_VALUES;
    for (int i = 0; i < NUM_VALUES; i++) {         // loop through all the keys
      if (root.containsKey(jsonCommandKeys[i])) {  // Match is found, I holds the correct ENUM reference for the state
        auto map_item = jsonStateMap.find(i);      // This returns an iterator type
        dataTypes data_type = map_item->second;
        std::cout << "i = " << i << " cmd: " << jsonCommandKeys[i] << " ,Data type: " << typeNames[data_type] << std::endl;  //
        // then deal with data depending on state
        jsonRX_data.cmdState = i;
        jsonRX_data.cmd_received = true;
        return jsonRX_data;                        // return the structure as the data has been extracted
      }
    }
  }
  return jsonRX_data;
}