

#include "jsonMessenger.h"


jsonMessenger::jsonMessenger() {
}


void jsonMessenger::jsonBegin() {
  Serial.begin(115200);
  Serial.println(F("{\"json\":\"Messenger\", \"version\":\"V0.0.0\"}"));
}




void jsonMessenger::printJSON(StaticJsonDocument<JSON_RX_SIZE> jsonDoc) {
#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
  serializeJsonPretty(jsonDoc, Serial);
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
  serializeJson(jsonDoc, Serial);
#endif
  Serial.print(F("\n"));
}





jsonStateData jsonMessenger::jsonReadSerialLoop() {
  bool commandParsed = false;
  int error = 0;
  char command[JSON_RX_SIZE];
  jsonStateData jsonRX_data = { NONE, EMPTY, 0, 0.0, "", false };


  if (Serial.available() > 0) {
    // create JSON document
    StaticJsonDocument<JSON_RX_SIZE> jsonRXdoc;

    // Receive Command
    Serial.readBytesUntil(10, command, JSON_RX_SIZE);  // 10 = "\n"
    Serial.print(F("\ncommand received: "));
    Serial.println(command);

    // Analyse data
    deserializeJson(jsonRXdoc, command);
    JsonObject root = jsonRXdoc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"
                                                   // Now to parse the JSON message
                                                   // First get number of elements in the jsonStates enum numValues = NUM_VALUES;
                                                   // Then loop through all keys & see if root contains key
    for (int i = 0; i < NUM_VALUES; i++) {         // loop through all the keys
      if (root.containsKey(jsonCommandKeys[i])) {  // Match is found, i holds the correct ENUM reference for the state

        // jsonStates newState = static_cast<jsonStates>(i);    // Cast int to explicit enum type   // this doesnt seem to clear up any errors

        // jsonStates newState = i;
        auto map_item = jsonStateMap.find(i);    // This returns an iterator type
        dataTypes data_type = map_item->second;  // the second value contains the dataType enum



        // Set the flags to trigger the state change
        // jsonRX_data.cmdState = newState;
        jsonRX_data.cmdState = i;
        jsonRX_data.cmd_received = true;  //

        // then deal with data depending on state
        const char databuffer[16];  // Create a buffer to hold text string    #TODO ISSUE IS HERE LIKELY take out * to


        // Copy data into both correct place in data structure, and convert to string for debugging printing
        if (data_type == EMPTY) {
          strcpy(databuffer, "empty");

        } else if (data_type == INTEGER) {                      // Example of how to deal with different datatypes returned from jsonMessenger object
          itoa(jsonRXdoc[jsonCommandKeys[i]], databuffer, 10);  // 10: base 10 // If integer copy integer to string
          jsonRX_data.numeric = jsonRXdoc[jsonCommandKeys[i]];
          jsonRX_data.data_type = INTEGER;
        } else if (data_type == FLOAT) {
          dtostrf(jsonRXdoc[jsonCommandKeys[i]], 2, 2, databuffer);
          jsonRX_data.data = jsonRXdoc[jsonCommandKeys[i]];
          jsonRX_data.data_type = FLOAT;
        } else if (data_type == CHAR_ARRAY) {  // TODO FIND SAFER METHOD FOR THIS
                                               // int length = sizeof(root[jsonCommandKeys[i]]);
                                               // while (jsonRXdoc[jsonCommandKeys[i]][length] != "\0" ){
                                               //    length++;
                                               //   std::cout << "counting . . . " << length  << std::endl;
                                               // }
                                               // std::cout << "length:" << length << std::endl;
                                               // strcpy(databuffer, jsonRXdoc[jsonCommandKeys[i]]);  // THIS ONE WORK JUST IS NOT SAFE
                                               //databuffer[15] = "\0";
          snprintf(databuffer, "%.15s\0", root[jsonCommandKeys[i]]);
          snprintf(jsonRX_data.msg, "%.15s\0", root[jsonCommandKeys[i]]);
          // strcpy(jsonRX_data.msg, jsonRXdoc[jsonCommandKeys[i]]);  // This does allow string overloading and CANNOT BE CONSIDERED SAFE
          //jsonRX_data.msg[15] = "\0";
          jsonRX_data.data_type = CHAR_ARRAY;

        } else {
          std::cout << "Exception in State Definitions" << std::endl;
        }

        // Debug Output from JSON parser
        //std::cout << "i = " << i << " cmd: " << jsonCommandKeys[i] << " , Data type: " << typeNames[data_type] << std::endl;  //
        char buffer[64];
        sprintf(buffer, "i = %i, cmd: %s, data-type: %s, data: %s", i, jsonCommandKeys[i], typeNames[data_type], databuffer);
        Serial.println(buffer);


        return jsonRX_data;  // return the structure as the data has been extracted
      } else {
        // root did not contain key, but command could be further analysed to see if any other data
      }
    }
  }
  return jsonRX_data;
}
