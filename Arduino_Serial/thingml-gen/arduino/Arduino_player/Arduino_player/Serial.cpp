#include "Serial.h"
/*****************************************************/
//                    Serial
/*****************************************************/

#define Serial_BAUDRATE 115200
#define Serial_MAX_LOOP 28
#define Serial_MAX_MSG_SIZE 14
/*OTHER_VARS*/


#define Serial_LISTENER_STATE_IDLE 0
#define Serial_LISTENER_STATE_READING 1
#define Serial_LISTENER_STATE_ESCAPE 2
#define Serial_LISTENER_STATE_ERROR 3


#define Serial_START_BYTE 18
#define Serial_STOP_BYTE 19
#define Serial_ESCAPE_BYTE 125

struct Serial_instance_type Serial_instance;


void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id);

void Serial_setup() {
  Serial.begin(Serial_BAUDRATE);
}

void Serial_set_listener_id(uint16_t id) {
  Serial_instance.listener_id = id;
}

void Serial_forwardMessage(byte * msg, uint8_t size) {
  Serial.write(Serial_START_BYTE);
  for(uint8_t i = 0; i < size; i++) {
	if(msg[i] == Serial_ESCAPE_BYTE || msg[i] == Serial_START_BYTE || msg[i] == Serial_STOP_BYTE) {
    	Serial.write(Serial_ESCAPE_BYTE);
	}
    Serial.write(msg[i]);
  }
  Serial.write(Serial_STOP_BYTE);
}

void Serial_parser(byte * msg, uint16_t size) {
externalMessageEnqueue((uint8_t *) msg, size, Serial_instance.listener_id);
}


uint8_t Serial_serialListenerState = 0;
uint8_t Serial_msg_buf[Serial_MAX_MSG_SIZE];
uint16_t Serial_msg_index = 0;
uint8_t Serial_incoming = 0;

void Serial_read() {
  byte limit = 0;
  while ((Serial.available()) && (limit < Serial_MAX_LOOP)) {
   limit++;
    Serial_incoming = Serial.read();
    
    switch(Serial_serialListenerState) {
      case Serial_LISTENER_STATE_IDLE:
        if(Serial_incoming == Serial_START_BYTE) {
          Serial_serialListenerState = Serial_LISTENER_STATE_READING;
          Serial_msg_index = 0;
        }
      break;
      
      case Serial_LISTENER_STATE_READING:
        if (Serial_msg_index > Serial_MAX_MSG_SIZE) {
          Serial_serialListenerState = Serial_LISTENER_STATE_ERROR;
        } else {
          if(Serial_incoming == Serial_STOP_BYTE) {
            Serial_serialListenerState = Serial_LISTENER_STATE_IDLE;
            
            
            Serial_parser(Serial_msg_buf, Serial_msg_index);
            
          } else if (Serial_incoming == Serial_ESCAPE_BYTE) {
            Serial_serialListenerState = Serial_LISTENER_STATE_ESCAPE;
          } else {
            Serial_msg_buf[Serial_msg_index] = Serial_incoming;
            Serial_msg_index++;
          }
        }
      break;
      
      case Serial_LISTENER_STATE_ESCAPE:
        if (Serial_msg_index >= Serial_MAX_MSG_SIZE) {
          Serial_serialListenerState = Serial_LISTENER_STATE_ERROR;
        } else {
          Serial_msg_buf[Serial_msg_index] = Serial_incoming;
          Serial_msg_index++;
          Serial_serialListenerState = Serial_LISTENER_STATE_READING;
        }
      break;
      
      case Serial_LISTENER_STATE_ERROR:
        Serial_serialListenerState = Serial_LISTENER_STATE_IDLE;
        Serial_msg_index = 0;
      break;
    }
  }
  
}

/*FORWARDERS*/