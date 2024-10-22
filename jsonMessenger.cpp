

#include "jsonMessenger.h"


jsonMessenger::jsonMessenger() {
}


void jsonMessenger::jsonBegin() {
  // Serial.begin(115200);
  Serial.println(F("{\"json\":\"Messenger\", \"version\":\"V0.1.0\"}"));
}




void jsonMessenger::printJSON(StaticJsonDocument<JSON_RX_SIZE> *jsonDoc) {
#if PRETTY_PRINT_JSON == true
#pragma JSON set to Pretty Print !-May experience problems with Machine Parsing
  serializeJsonPretty(*jsonDoc, Serial);
#else
#pragma JSON set to standard JSON output - For human readability try enabling Pretty Print !
  serializeJson(*jsonDoc, Serial);
#endif
  Serial.print(F("\n"));
}





jsonStateData jsonMessenger::jsonReadSerialLoop() {

  jsonStateData jsonRX_data = { NONE, EMPTY, 0, 0.0, "", false };

  if (Serial.available() > 0) {
    //char command[JSON_RX_SIZE];
    // create JSON document
    StaticJsonDocument<JSON_RX_SIZE> jsonRXdoc;
    // Receive Command
    // Serial.readBytesUntil(10, command, JSON_RX_SIZE);  // 10 = "\n"
    // Serial.print(F("\ncmd rxed: "));
    // Serial.println(command);

    //Serial.read();  // clear any additional data left in the buffer

    // NEW FUNCTION, try deserializing directly from stream
    deserializeJson(jsonRXdoc, Serial);

    //deserializeJson(jsonRXdoc, command);
    JsonObject root = jsonRXdoc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"
                                                   // Now to parse the JSON message
                                                   // First get number of elements in the jsonStates enum numValues = NUM_VALUES;
                                                   // Then loop through all keys & see if root contains key
    for (int i = 0; i < NUM_VALUES; i++) {         // loop through all the keys
      if (root.containsKey(jsonCommandKeys[i])) {  // Match is found, i holds the correct ENUM reference for the state

        // jsonStates newState = static_cast<jsonStates>(i);    // Cast int to explicit enum type   // this doesnt seem to clear up any errors
        // jsonStates newState = i;
        auto map_item = jsonStateMap.find(i);      // This returns an iterator type
                                                   //  dataTypes data_type = map_item->second;  // the second value contains the dataType enum
        jsonRX_data.data_type = map_item->second;  // the second value contains the dataType enum (trying to cut out some middleman vars that are not doing anything)

        // Set the flags to trigger the state change
        // jsonRX_data.cmdState = newState;
        jsonRX_data.cmdState = i;
        jsonRX_data.cmd_received = true;  //Set flag to be passed outside of library and notify a command has been sent (depreciated if using queue)


        //   char databuffer[16];  // Create a buffer to hold text string    #TODO ISSUE IS HERE LIKELY take out * to


        // Copy data into  correct place in data structure, and convert to string for debugging printing

        // then deal with data depending on state
        if (jsonRX_data.data_type == EMPTY) {
          //  strcpy(databuffer, "empty");
        } else if (jsonRX_data.data_type == INTEGER) {  // Example of how to deal with different datatypes returned from jsonMessenger object
                                                        //  itoa(jsonRXdoc[jsonCommandKeys[i]], databuffer, 10);  // 10: base 10 // If integer copy integer to string
          jsonRX_data.numeric = jsonRXdoc[jsonCommandKeys[i]].as<uint16_t>();
          // jsonRX_data.data_type = INTEGER;
        } else if (jsonRX_data.data_type == FLOAT) {
          // dtostrf(jsonRXdoc[jsonCommandKeys[i]], 2, 2, databuffer);
          jsonRX_data.data = jsonRXdoc[jsonCommandKeys[i]].as<float>();
          // jsonRX_data.data_type = FLOAT;
        } else if (jsonRX_data.data_type == CSTRING) {
          const char *extracted = jsonRXdoc[jsonCommandKeys[i]].as<const char *>();  //

          // memcpy(databuffer, extracted, JSON_MSG_LENGTH);

          memcpy(jsonRX_data.msg, extracted, JSON_MSG_LENGTH);
          //databuffer[JSON_MSG_LENGTH - 1] = '\0';
          jsonRX_data.msg[JSON_MSG_LENGTH - 1] = '\0';
          //  jsonRX_data.data_type = CSTRING;
        } else {
          Serial.println(F("dataType exception"));
        }
#if JSON_USE_QUEUE == true
        if (jsonMessenger::enque_cmd(&jsonRX_data) == -1) {
          Serial.println(F("Enque cmd failed"));
        }
#endif
        return jsonRX_data;  // return the structure as the data has been extracted
      } else {
        // root did not contain key, but command could be further analysed to see if any other data
        //std::cout << "Key not found in JSON root" << std::endl;
      }
    }
  }
  return jsonRX_data;
}



void jsonMessenger::printCMDkey(jsonStates state) {
  std::cout << jsonCommandKeys[state] << "\0";
}

void jsonMessenger::printDataType(dataTypes type) {
  std::cout << typeNames[type] << "\0";
}

void jsonMessenger::printJSONdata(jsonStateData *data) {  // Use -> to assess members of a pointer to a struct
  Serial.print(F("cmdState: "));
  jsonMessenger::printCMDkey(data->cmdState);
  Serial.print(F(" dataType: "));
  jsonMessenger::printDataType(data->data_type);
  Serial.print(F(" Numeric: "));
  Serial.print(data->numeric);
  Serial.print(F(" Float: "));
  Serial.print(data->data);
  Serial.print(F(" msg: "));
  Serial.print(data->msg);
  Serial.print(F(" cmd: "));
  Serial.print(data->cmd_received);
  Serial.println();
}


// Returns the number of items in the queue, or -1 on fail
int8_t jsonMessenger::enque_cmd(jsonStateData *newItem) {
  Serial.print(F("enque -> length:  "));
  if (queue_size < CMD_QUEUE_LENGTH) {
    jsonQueue[queue_size] = *newItem;
    queue_size++;
    Serial.println(queue_size);
    return queue_size;
  } else {
    Serial.println(-1);
    return -1;
  }
}



// returns first queue item or 0 if queue is empty when called
jsonStateData jsonMessenger::dequeue_cmd() {
  jsonStateData first_item = { NONE, EMPTY, 0, 0.0, "", false };
  if (queue_size > 0) {
    jsonStateData first_item = jsonQueue[0];

    for (int i = 0; i < queue_size; i++) {
      //std::cout << "i: " << i << " i+1: " << i + 1 << std::endl;
      jsonQueue[i] = jsonQueue[i + 1];
    }
    queue_size--;
    Serial.print(F("Dequeue -> length:  "));
    Serial.println(queue_size);
    return first_item;
  } else {
    return first_item;
  }
}
