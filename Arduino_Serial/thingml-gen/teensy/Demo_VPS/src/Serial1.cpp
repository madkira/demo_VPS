#include "Serial1.h"
/*****************************************************/
//                    Serial1
/*****************************************************/

#define Serial1_BAUDRATE 115200
#define Serial1_MAX_LOOP 0
#define Serial1_MAX_MSG_SIZE 0
/*OTHER_VARS*/


#define Serial1_LISTENER_STATE_IDLE 0
#define Serial1_LISTENER_STATE_READING 1
#define Serial1_LISTENER_STATE_ESCAPE 2
#define Serial1_LISTENER_STATE_ERROR 3


#define Serial1_START_BYTE 18
#define Serial1_STOP_BYTE 19
#define Serial1_ESCAPE_BYTE 125

struct Serial1_instance_type Serial1_instance;


void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id);

void Serial1_setup() {
  Serial1.begin(Serial1_BAUDRATE);
}

void Serial1_set_listener_id(uint16_t id) {
  Serial1_instance.listener_id = id;
}

void Serial1_forwardMessage(byte * msg, uint8_t size) {
  Serial1.write(Serial1_START_BYTE);
  for(uint8_t i = 0; i < size; i++) {
	if(msg[i] == Serial1_ESCAPE_BYTE || msg[i] == Serial1_START_BYTE || msg[i] == Serial1_STOP_BYTE) {
    	Serial1.write(Serial1_ESCAPE_BYTE);
	}
    Serial1.write(msg[i]);
  }
  Serial1.write(Serial1_STOP_BYTE);
}

void Serial1_parser(byte * msg, uint16_t size) {
}


uint8_t Serial1_serialListenerState = 0;
uint8_t Serial1_msg_buf[Serial1_MAX_MSG_SIZE];
uint16_t Serial1_msg_index = 0;
uint8_t Serial1_incoming = 0;

void Serial1_read() {
  byte limit = 0;
  while ((Serial1.available()) && (limit < Serial1_MAX_LOOP)) {
   limit++;
    Serial1_incoming = Serial1.read();
    
    switch(Serial1_serialListenerState) {
      case Serial1_LISTENER_STATE_IDLE:
        if(Serial1_incoming == Serial1_START_BYTE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_READING;
          Serial1_msg_index = 0;
        }
      break;
      
      case Serial1_LISTENER_STATE_READING:
        if (Serial1_msg_index > Serial1_MAX_MSG_SIZE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_ERROR;
        } else {
          if(Serial1_incoming == Serial1_STOP_BYTE) {
            Serial1_serialListenerState = Serial1_LISTENER_STATE_IDLE;
            
            
            Serial1_parser(Serial1_msg_buf, Serial1_msg_index);
            
          } else if (Serial1_incoming == Serial1_ESCAPE_BYTE) {
            Serial1_serialListenerState = Serial1_LISTENER_STATE_ESCAPE;
          } else {
            Serial1_msg_buf[Serial1_msg_index] = Serial1_incoming;
            Serial1_msg_index++;
          }
        }
      break;
      
      case Serial1_LISTENER_STATE_ESCAPE:
        if (Serial1_msg_index >= Serial1_MAX_MSG_SIZE) {
          Serial1_serialListenerState = Serial1_LISTENER_STATE_ERROR;
        } else {
          Serial1_msg_buf[Serial1_msg_index] = Serial1_incoming;
          Serial1_msg_index++;
          Serial1_serialListenerState = Serial1_LISTENER_STATE_READING;
        }
      break;
      
      case Serial1_LISTENER_STATE_ERROR:
        Serial1_serialListenerState = Serial1_LISTENER_STATE_IDLE;
        Serial1_msg_index = 0;
      break;
    }
  }
  
}

/*FORWARDERS*/// Forwarding of messages Serial1::Demo::serial1sender::calibrating
void forward_Serial1_Demo_send_serial1sender_calibrating(struct Demo_Instance *_instance){
byte forward_buf[2];
forward_buf[0] = (3 >> 8) & 0xFF;
forward_buf[1] =  3 & 0xFF;


//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 2);
}

// Forwarding of messages Serial1::Demo::serial1sender::noSignal
void forward_Serial1_Demo_send_serial1sender_noSignal(struct Demo_Instance *_instance){
byte forward_buf[2];
forward_buf[0] = (2 >> 8) & 0xFF;
forward_buf[1] =  2 & 0xFF;


//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 2);
}

// Forwarding of messages Serial1::Demo::serial1sender::play
void forward_Serial1_Demo_send_serial1sender_play(struct Demo_Instance *_instance){
byte forward_buf[2];
forward_buf[0] = (4 >> 8) & 0xFF;
forward_buf[1] =  4 & 0xFF;


//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 2);
}

// Forwarding of messages Serial1::Demo::serial1sender::positionsend
void forward_Serial1_Demo_send_serial1sender_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z){
byte forward_buf[14];
forward_buf[0] = (1 >> 8) & 0xFF;
forward_buf[1] =  1 & 0xFF;


// parameter x
union u_x_t {
uint32_t p;
byte bytebuffer[4];
} u_x;
u_x.p = x;
forward_buf[2] =  (u_x.bytebuffer[3] & 0xFF);
forward_buf[3] =  (u_x.bytebuffer[2] & 0xFF);
forward_buf[4] =  (u_x.bytebuffer[1] & 0xFF);
forward_buf[5] =  (u_x.bytebuffer[0] & 0xFF);

// parameter y
union u_y_t {
uint32_t p;
byte bytebuffer[4];
} u_y;
u_y.p = y;
forward_buf[6] =  (u_y.bytebuffer[3] & 0xFF);
forward_buf[7] =  (u_y.bytebuffer[2] & 0xFF);
forward_buf[8] =  (u_y.bytebuffer[1] & 0xFF);
forward_buf[9] =  (u_y.bytebuffer[0] & 0xFF);

// parameter z
union u_z_t {
uint32_t p;
byte bytebuffer[4];
} u_z;
u_z.p = z;
forward_buf[10] =  (u_z.bytebuffer[3] & 0xFF);
forward_buf[11] =  (u_z.bytebuffer[2] & 0xFF);
forward_buf[12] =  (u_z.bytebuffer[1] & 0xFF);
forward_buf[13] =  (u_z.bytebuffer[0] & 0xFF);

//Forwarding with specified function 
Serial1_forwardMessage(forward_buf, 14);
}

