/*****************************************************************************
 * Headers for type : Demo
 *****************************************************************************/


// BEGIN: Code from the c_header annotation Demo

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

// END: Code from the c_header annotation Demo

// Definition of the instance struct:
struct Demo_Instance {

// Instances of different sessions
bool active;
// Variables for the ID of the ports of the instance
uint16_t id_Output;
uint16_t id_Timer;
uint16_t id_process;
// Variables for the current instance state
int Demo_Demo_Reach_Zone_State;
// Variables for the properties of the instance

};
// generateEventHandlers2
int Demo_handle_empty_event(struct Demo_Instance *_instance);
// Declaration of prototypes outgoing messages :
void Demo_Demo_Reach_Zone_OnEntry(int state, struct Demo_Instance *_instance);
void Demo_handle_Timer_timer_timeout(struct Demo_Instance *_instance, uint8_t id);
void Demo_handle_Output_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z);
void Demo_handle_Output_noSignal(struct Demo_Instance *_instance);
// Declaration of callbacks for incoming messages:
void register_Demo_send_Timer_timer_start_listener(void (*_listener)(struct Demo_Instance *, uint8_t, uint32_t));
void register_external_Demo_send_Timer_timer_start_listener(void (*_listener)(struct Demo_Instance *, uint8_t, uint32_t));
void register_Demo_send_Timer_timer_cancel_listener(void (*_listener)(struct Demo_Instance *, uint8_t));
void register_external_Demo_send_Timer_timer_cancel_listener(void (*_listener)(struct Demo_Instance *, uint8_t));

// Definition of the states:
#define DEMO_DEMO_REACH_ZONE_STATE 0
#define DEMO_DEMO_REACH_ZONE_IDLE_STATE 1
#define DEMO_DEMO_REACH_ZONE_SETPOINT_STATE 2
#define DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE 3


/*****************************************************/
//                    Serial
/*****************************************************/
struct Serial_instance_type {
    uint16_t listener_id;
    //Connector
};
extern struct Serial_instance_type Serial_instance;

void Serial_setup();

void Serial_set_listener_id(uint16_t id);

void Serial_forwardMessage(byte * msg, uint8_t size);

void Serial_read();

/********************* FORWARDERS *********************/

/*FORWARDERS*/
struct timer2_instance_type {
    uint16_t listener_id;
    /*INSTANCE_INFORMATION*/
};
extern struct timer2_instance_type timer2_instance;

void timer2_setup();
void timer2_read();

//void forward_timer2_SoftButton_send_Timer_timer_start(struct SoftButton_Instance *_instance, uint8_t id, uint32_t time);
//void forward_timer2_SoftButton_send_Timer_timer_cancel(struct SoftButton_Instance *_instance, uint8_t id);
void forward_timer2_Demo_send_Timer_timer_start(struct Demo_Instance *_instance, uint8_t id, uint32_t time);
void forward_timer2_Demo_send_Timer_timer_cancel(struct Demo_Instance *_instance, uint8_t id);

/* Adds and instance to the runtime and returns its id */
uint16_t add_instance(void * instance_struct);
/* Returns the instance with id */
void * instance_by_id(uint16_t id);

/* Returns the number of byte currently in the fifo */
int fifo_byte_length();
/* Returns the number of bytes currently available in the fifo */
int fifo_byte_available();
/* Returns true if the fifo is empty */
int fifo_empty();
/* Return true if the fifo is full */
int fifo_full();
/* Enqueue 1 byte in the fifo if there is space
   returns 1 for sucess and 0 if the fifo was full */
int fifo_enqueue(byte b);
/* Enqueue 1 byte in the fifo without checking for available space
   The caller should have checked that there is enough space */
int _fifo_enqueue(byte b);
/* Dequeue 1 byte in the fifo.
   The caller should check that the fifo is not empty */
byte fifo_dequeue();

#define MAX_INSTANCES 5
#define FIFO_SIZE 256

/*********************************
 * Instance IDs and lookup
 *********************************/

void * instances[MAX_INSTANCES];
uint16_t instances_count = 0;

void * instance_by_id(uint16_t id) {
  return instances[id];
}

uint16_t add_instance(void * instance_struct) {
  instances[instances_count] = instance_struct;
  return instances_count++;
}

/******************************************
 * Simple byte FIFO implementation
 ******************************************/

byte fifo[FIFO_SIZE];
int fifo_head = 0;
int fifo_tail = 0;

// Returns the number of byte currently in the fifo
int fifo_byte_length() {
  if (fifo_tail >= fifo_head)
    return fifo_tail - fifo_head;
  return fifo_tail + FIFO_SIZE - fifo_head;
}

// Returns the number of bytes currently available in the fifo
int fifo_byte_available() {
  return FIFO_SIZE - 1 - fifo_byte_length();
}

// Returns true if the fifo is empty
int fifo_empty() {
  return fifo_head == fifo_tail;
}

// Return true if the fifo is full
int fifo_full() {
  return fifo_head == ((fifo_tail + 1) % FIFO_SIZE);
}

// Enqueue 1 byte in the fifo if there is space
// returns 1 for sucess and 0 if the fifo was full
int fifo_enqueue(byte b) {
  int new_tail = (fifo_tail + 1) % FIFO_SIZE;
  if (new_tail == fifo_head) return 0; // the fifo is full
  fifo[fifo_tail] = b;
  fifo_tail = new_tail;
  return 1;
}

// Enqueue 1 byte in the fifo without checking for available space
// The caller should have checked that there is enough space
int _fifo_enqueue(byte b) {
  fifo[fifo_tail] = b;
  fifo_tail = (fifo_tail + 1) % FIFO_SIZE;
  return 0; // Dummy added by steffend
}

// Dequeue 1 byte in the fifo.
// The caller should check that the fifo is not empty
byte fifo_dequeue() {
  if (!fifo_empty()) {
    byte result = fifo[fifo_head];
    fifo_head = (fifo_head + 1) % FIFO_SIZE;
    return result;
  }
  return 0;
}

/*****************************************************************************
 * Implementation for type : Demo
 *****************************************************************************/


// BEGIN: Code from the c_global annotation Demo

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define DOT 2
#define CIRCLE 4

uint8_t old_x;
uint8_t old_y;

uint8_t cur_x;
uint8_t cur_y;

uint8_t tar_x;
uint8_t tar_y;

uint8_t Score = 0;


// END: Code from the c_global annotation Demo

// Declaration of prototypes:
//Prototypes: State Machine
void Demo_Demo_Reach_Zone_OnExit(int state, struct Demo_Instance *_instance);
//Prototypes: Message Sending
void Demo_send_Timer_timer_start(struct Demo_Instance *_instance, uint8_t id, uint32_t time);
void Demo_send_Timer_timer_cancel(struct Demo_Instance *_instance, uint8_t id);
//Prototypes: Function
// Declaration of functions:

// Sessions functionss:


// On Entry Actions:
void Demo_Demo_Reach_Zone_OnEntry(int state, struct Demo_Instance *_instance) {
switch(state) {
case DEMO_DEMO_REACH_ZONE_STATE:{
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_IDLE_STATE;

			tft.initR(INITR_144GREENTAB);
  			tft.setRotation(3);
			tft.fillScreen(ST7735_BLACK);
			
Demo_Demo_Reach_Zone_OnEntry(_instance->Demo_Demo_Reach_Zone_State, _instance);
break;
}
case DEMO_DEMO_REACH_ZONE_IDLE_STATE:{

			Score = 0;
			tft.fillScreen(ST7735_BLACK);
		    tar_x = 64;
		    tar_y = 64;
			
break;
}
case DEMO_DEMO_REACH_ZONE_SETPOINT_STATE:{

			tft.fillScreen(ST7735_BLACK);
			old_x = 0;
			old_y = 0;
			cur_x = 0;
			cur_y = 0;
			tar_x = random(128);
			tar_y = random(128);
			
break;
}
case DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE:{

				tft.fillScreen(ST7735_BLACK);
			    tft.setCursor(40, 30);
			    tft.setTextColor(ST7735_RED);
			    tft.setTextSize(1);
			    tft.println("Game Over");
			    tft.setTextColor(ST7735_YELLOW);
			    tft.setCursor(60, 50);
			    tft.setTextSize(4);
			    tft.println(Score);
				
Demo_send_Timer_timer_start(_instance, 0, 5000);
break;
}
default: break;
}
}

// On Exit Actions:
void Demo_Demo_Reach_Zone_OnExit(int state, struct Demo_Instance *_instance) {
switch(state) {
case DEMO_DEMO_REACH_ZONE_STATE:{
Demo_Demo_Reach_Zone_OnExit(_instance->Demo_Demo_Reach_Zone_State, _instance);
break;}
case DEMO_DEMO_REACH_ZONE_IDLE_STATE:{
break;}
case DEMO_DEMO_REACH_ZONE_SETPOINT_STATE:{
break;}
case DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE:{
break;}
default: break;
}
}

// Event Handlers for incoming messages:
void Demo_handle_Timer_timer_timeout(struct Demo_Instance *_instance, uint8_t id) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_SETPOINT_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE;
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE, _instance);
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
else if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_IDLE_STATE;
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_IDLE_STATE, _instance);
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
//End Region Demo_Reach_Zone
//End dsregion Demo_Reach_Zone
//Session list: 
}
void Demo_handle_Output_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_IDLE_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {

				old_x = cur_x;
				old_y = cur_y;
				cur_y = int(x/1000);
				cur_x = int(y/1000);
				tft.fillCircle(old_x, old_y, DOT, ST7735_BLACK);
			    tft.setCursor(0, 30);
		    	tft.setTextColor(ST7735_RED);
		    	tft.setTextSize(1);
		    	tft.println("Reach the center to Start");
			    tft.drawCircle(tar_x, tar_y, CIRCLE, ST7735_YELLOW);
				tft.fillCircle(cur_x, cur_y, DOT, ST7735_GREEN);
				
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
else if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {

				old_x = cur_x;
				old_y = cur_y;
				cur_y = int(x/1000);
				cur_x = int(y/1000);
				tft.fillCircle(old_x, old_y, DOT, ST7735_BLACK);
			    tft.drawCircle(tar_x, tar_y, CIRCLE, ST7735_YELLOW);
				tft.fillCircle(cur_x, cur_y, DOT, ST7735_GREEN);
				
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
//End Region Demo_Reach_Zone
//End dsregion Demo_Reach_Zone
//Session list: 
}
void Demo_handle_Output_noSignal(struct Demo_Instance *_instance) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_IDLE_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
tft.fillCircle(cur_x, cur_y, DOT, ST7735_RED);
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
else if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
tft.fillCircle(cur_x, cur_y, DOT, ST7735_RED);
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
//End Region Demo_Reach_Zone
//End dsregion Demo_Reach_Zone
//Session list: 
}
int Demo_handle_empty_event(struct Demo_Instance *_instance) {
 uint8_t empty_event_consumed = 0;
if(!(_instance->active)) return 0;
//Region Demo_Reach_Zone
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_IDLE_STATE) {
if ((cur_x - tar_x)*(cur_x - tar_x) + (cur_y - tar_y)*(cur_y - tar_y) < CIRCLE*CIRCLE) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_IDLE_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_SETPOINT_STATE;
Demo_send_Timer_timer_start(_instance, 0, 30000);
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_SETPOINT_STATE, _instance);
return 1;
}
}
else if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if ((cur_x - tar_x)*(cur_x - tar_x) + (cur_y - tar_y)*(cur_y - tar_y) < CIRCLE*CIRCLE) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_SETPOINT_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_SETPOINT_STATE;
Score++;
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_SETPOINT_STATE, _instance);
return 1;
}
}
//begin dispatchEmptyToSession
//end dispatchEmptyToSession
return empty_event_consumed;
}

// Observers for outgoing messages:
void (*external_Demo_send_Timer_timer_start_listener)(struct Demo_Instance *, uint8_t, uint32_t)= 0x0;
void (*Demo_send_Timer_timer_start_listener)(struct Demo_Instance *, uint8_t, uint32_t)= 0x0;
void register_external_Demo_send_Timer_timer_start_listener(void (*_listener)(struct Demo_Instance *, uint8_t, uint32_t)){
external_Demo_send_Timer_timer_start_listener = _listener;
}
void register_Demo_send_Timer_timer_start_listener(void (*_listener)(struct Demo_Instance *, uint8_t, uint32_t)){
Demo_send_Timer_timer_start_listener = _listener;
}
void Demo_send_Timer_timer_start(struct Demo_Instance *_instance, uint8_t id, uint32_t time){
if (Demo_send_Timer_timer_start_listener != 0x0) Demo_send_Timer_timer_start_listener(_instance, id, time);
if (external_Demo_send_Timer_timer_start_listener != 0x0) external_Demo_send_Timer_timer_start_listener(_instance, id, time);
;
}
void (*external_Demo_send_Timer_timer_cancel_listener)(struct Demo_Instance *, uint8_t)= 0x0;
void (*Demo_send_Timer_timer_cancel_listener)(struct Demo_Instance *, uint8_t)= 0x0;
void register_external_Demo_send_Timer_timer_cancel_listener(void (*_listener)(struct Demo_Instance *, uint8_t)){
external_Demo_send_Timer_timer_cancel_listener = _listener;
}
void register_Demo_send_Timer_timer_cancel_listener(void (*_listener)(struct Demo_Instance *, uint8_t)){
Demo_send_Timer_timer_cancel_listener = _listener;
}
void Demo_send_Timer_timer_cancel(struct Demo_Instance *_instance, uint8_t id){
if (Demo_send_Timer_timer_cancel_listener != 0x0) Demo_send_Timer_timer_cancel_listener(_instance, id);
if (external_Demo_send_Timer_timer_cancel_listener != 0x0) external_Demo_send_Timer_timer_cancel_listener(_instance, id);
;
}



#define timer2_NB_SOFT_TIMER 4
uint32_t timer2_timer[timer2_NB_SOFT_TIMER];
uint32_t  timer2_prev_1sec = 0;



void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id);

uint8_t timer2_interrupt_counter = 0;
SIGNAL(TIMER2_OVF_vect) {
TCNT2 = 5;
timer2_interrupt_counter++;
if(timer2_interrupt_counter >= 0) {
timer2_interrupt_counter = 0;
}
}



//struct timer2_instance_type {
//    uint16_t listener_id;
//    /*INSTANCE_INFORMATION*/
//} timer2_instance;

struct timer2_instance_type timer2_instance;


void timer2_setup() {
	// Run timer2 interrupt up counting at 250kHz 
		 TCCR2A = 0;
		 TCCR2B = 1<<CS22 | 0<<CS21 | 0<<CS20;
		
		 //Timer2 Overflow Interrupt Enable
		 TIMSK2 |= 1<<TOIE2;


	timer2_prev_1sec = millis() + 1000;
}

void timer2_set_listener_id(uint16_t id) {
	timer2_instance.listener_id = id;
}

void timer2_timer_start(uint8_t id, uint32_t ms) {
if(id <timer2_NB_SOFT_TIMER) {
timer2_timer[id] = ms + millis();
}
}

void timer2_timer_cancel(uint8_t id) {
if(id <timer2_NB_SOFT_TIMER) {
timer2_timer[id] = 0;
}
}

void timer2_timeout(uint8_t id) {
uint8_t enqueue_buf[3];
enqueue_buf[0] = (3 >> 8) & 0xFF;
enqueue_buf[1] = 3 & 0xFF;
enqueue_buf[2] = id;
externalMessageEnqueue(enqueue_buf, 3, timer2_instance.listener_id);
}





void timer2_read() {
    uint32_t tms = millis();
    uint8_t t;
for(t = 0; t < 4; t++) {
if((timer2_timer[t] > 0) && (timer2_timer[t] < tms)) {
timer2_timer[t] = 0;
timer2_timeout(t);
}
}

    if (timer2_prev_1sec < tms) {
        timer2_prev_1sec += 1000;
    }
    
}
// Forwarding of messages timer2::Demo::Timer::timer_start
void forward_timer2_Demo_send_Timer_timer_start(struct Demo_Instance *_instance, uint8_t id, uint32_t time){
timer2_timer_start(id, time);}

// Forwarding of messages timer2::Demo::Timer::timer_cancel
void forward_timer2_Demo_send_Timer_timer_cancel(struct Demo_Instance *_instance, uint8_t id){
timer2_timer_cancel(id);}

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


/*****************************************************************************
 * Definitions for configuration : Arduino_player
 *****************************************************************************/

//Declaration of instance variables
//Instance player
// Variables for the properties of the instance
struct Demo_Instance player_var;
// Variables for the sessions of the instance




//New dispatcher for messages
void dispatch_ms8_tic(uint16_t sender) {
if (sender == player_var.id_process) {

}

}


//New dispatcher for messages
void dispatch_positionsend(uint16_t sender, uint32_t param_x, uint32_t param_y, uint32_t param_z) {
if (sender == player_var.id_process) {

}
if (sender == Serial_instance.listener_id) {
Demo_handle_Output_positionsend(&player_var, param_x, param_y, param_z);

}

}


//New dispatcher for messages
void dispatch_timer_cancel(uint16_t sender, uint8_t param_id) {
if (sender == player_var.id_process) {

}

}


//New dispatcher for messages
void dispatch_timer_start(uint16_t sender, uint8_t param_id, uint32_t param_time) {
if (sender == player_var.id_process) {

}

}


//New dispatcher for messages
void dispatch_noSignal(uint16_t sender) {
if (sender == player_var.id_process) {

}
if (sender == Serial_instance.listener_id) {
Demo_handle_Output_noSignal(&player_var);

}

}


//New dispatcher for messages
void dispatch_timer_timeout(uint16_t sender, uint8_t param_id) {
if (sender == player_var.id_process) {

}
if (sender == timer2_instance.listener_id) {
Demo_handle_Timer_timer_timeout(&player_var, param_id);

}

}


int processMessageQueue() {
if (fifo_empty()) return 0; // return 0 if there is nothing to do

uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 1:{
byte mbuf[16 - 2];
while (mbufi < (16 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_positionsend = 2;
union u_positionsend_x_t {
uint32_t p;
byte bytebuffer[4];
} u_positionsend_x;
u_positionsend_x.bytebuffer[3] = mbuf[mbufi_positionsend + 0];
u_positionsend_x.bytebuffer[2] = mbuf[mbufi_positionsend + 1];
u_positionsend_x.bytebuffer[1] = mbuf[mbufi_positionsend + 2];
u_positionsend_x.bytebuffer[0] = mbuf[mbufi_positionsend + 3];
mbufi_positionsend += 4;
union u_positionsend_y_t {
uint32_t p;
byte bytebuffer[4];
} u_positionsend_y;
u_positionsend_y.bytebuffer[3] = mbuf[mbufi_positionsend + 0];
u_positionsend_y.bytebuffer[2] = mbuf[mbufi_positionsend + 1];
u_positionsend_y.bytebuffer[1] = mbuf[mbufi_positionsend + 2];
u_positionsend_y.bytebuffer[0] = mbuf[mbufi_positionsend + 3];
mbufi_positionsend += 4;
union u_positionsend_z_t {
uint32_t p;
byte bytebuffer[4];
} u_positionsend_z;
u_positionsend_z.bytebuffer[3] = mbuf[mbufi_positionsend + 0];
u_positionsend_z.bytebuffer[2] = mbuf[mbufi_positionsend + 1];
u_positionsend_z.bytebuffer[1] = mbuf[mbufi_positionsend + 2];
u_positionsend_z.bytebuffer[0] = mbuf[mbufi_positionsend + 3];
mbufi_positionsend += 4;
dispatch_positionsend((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_positionsend_x.p /* x */ ,
 u_positionsend_y.p /* y */ ,
 u_positionsend_z.p /* z */ );
break;
}
case 2:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_noSignal = 2;
dispatch_noSignal((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
case 3:{
byte mbuf[5 - 2];
while (mbufi < (5 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_timer_timeout = 2;
union u_timer_timeout_id_t {
uint8_t p;
byte bytebuffer[1];
} u_timer_timeout_id;
u_timer_timeout_id.bytebuffer[0] = mbuf[mbufi_timer_timeout + 0];
mbufi_timer_timeout += 1;
dispatch_timer_timeout((mbuf[0] << 8) + mbuf[1] /* instance port*/,
 u_timer_timeout_id.p /* id */ );
break;
}
}
return 1;
}

void forward_Demo_send_Timer_timer_cancel(struct Demo_Instance *_instance, uint8_t id){
if(_instance->id_Timer == player_var.id_Timer) {
forward_timer2_Demo_send_Timer_timer_cancel(_instance, id);
}
}
void forward_Demo_send_Timer_timer_start(struct Demo_Instance *_instance, uint8_t id, uint32_t time){
if(_instance->id_Timer == player_var.id_Timer) {
forward_timer2_Demo_send_Timer_timer_start(_instance, id, time);
}
}

//external Message enqueue
void externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id) {
if ((msgSize >= 2) && (msg != NULL)) {
uint8_t msgSizeOK = 0;
switch(msg[0] * 256 + msg[1]) {
case 1:
if(msgSize == 14) {
msgSizeOK = 1;}
break;
case 2:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 3:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
}

if(msgSizeOK == 1) {
if ( fifo_byte_available() > (msgSize + 2) ) {
	uint8_t i;
	for (i = 0; i < 2; i++) {
		_fifo_enqueue(msg[i]);
	}
	_fifo_enqueue((listener_id >> 8) & 0xFF);
	_fifo_enqueue(listener_id & 0xFF);
	for (i = 2; i < msgSize; i++) {
		_fifo_enqueue(msg[i]);
	}
}
}
}
}

void initialize_configuration_Arduino_player() {
// Initialize connectors
register_external_Demo_send_Timer_timer_start_listener(&forward_Demo_send_Timer_timer_start);
register_external_Demo_send_Timer_timer_cancel_listener(&forward_Demo_send_Timer_timer_cancel);

// Init the ID, state variables and properties for external connector Serial
// Init the ID, state variables and properties for external connector timer2

// Network Initialization

Serial_instance.listener_id = add_instance(&Serial_instance);

Serial_setup();


timer2_instance.listener_id = add_instance(&timer2_instance);

timer2_setup();

// End Network Initialization

// Init the ID, state variables and properties for instance player
player_var.active = true;
player_var.id_Output = add_instance( (void*) &player_var);
player_var.id_Timer = add_instance( (void*) &player_var);
player_var.id_process = add_instance( (void*) &player_var);
player_var.Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_IDLE_STATE;

Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_STATE, &player_var);
}




void setup() {
initialize_configuration_Arduino_player();

}

void loop() {

// Network Listener
Serial_read();

timer2_read();
// End Network Listener

int emptyEventConsumed = 1;
while (emptyEventConsumed != 0) {
emptyEventConsumed = 0;
emptyEventConsumed += Demo_handle_empty_event(&player_var);
}

    processMessageQueue();
}
