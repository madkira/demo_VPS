#include "Demo.h"
#include "Serial.h"
#include "timer2.h"
#include "thingml_typedefs.h"
#include "runtime.h"



/*****************************************************************************
 * Definitions for configuration : Arduino_player
 *****************************************************************************/

//Declaration of instance variables
//Instance player
// Variables for the properties of the instance
struct Demo_Instance player_var;
// Variables for the sessions of the instance




//New dispatcher for messages
void dispatch_timer_cancel(uint16_t sender, uint8_t param_id) {
if (sender == player_var.id_process) {

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


//New dispatcher for messages
void dispatch_positionsend(uint16_t sender, uint32_t param_x, uint32_t param_y, uint32_t param_z) {
if (sender == player_var.id_process) {

}
if (sender == Serial_instance.listener_id) {
Demo_handle_Output_positionsend(&player_var, param_x, param_y, param_z);

}

}


//New dispatcher for messages
void dispatch_play(uint16_t sender) {
if (sender == player_var.id_process) {

}
if (sender == Serial_instance.listener_id) {
Demo_handle_Output_play(&player_var);

}

}


//New dispatcher for messages
void dispatch_s1_tic(uint16_t sender) {
if (sender == player_var.id_process) {

}
if (sender == timer2_instance.listener_id) {
Demo_handle_Timer_s1_tic(&player_var);

}

}


//New dispatcher for messages
void dispatch_calibrating(uint16_t sender) {
if (sender == player_var.id_process) {

}
if (sender == Serial_instance.listener_id) {
Demo_handle_Output_calibrating(&player_var);

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
void dispatch_timer_start(uint16_t sender, uint8_t param_id, uint32_t param_time) {
if (sender == player_var.id_process) {

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
case 5:{
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
case 4:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_play = 2;
dispatch_play((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
case 6:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_s1_tic = 2;
dispatch_s1_tic((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
case 3:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_calibrating = 2;
dispatch_calibrating((mbuf[0] << 8) + mbuf[1] /* instance port*/);
break;
}
case 2:{
byte mbuf[4 - 2];
while (mbufi < (4 - 2)) mbuf[mbufi++] = fifo_dequeue();
uint8_t mbufi_noSignal = 2;
dispatch_noSignal((mbuf[0] << 8) + mbuf[1] /* instance port*/);
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
case 5:
if(msgSize == 3) {
msgSizeOK = 1;}
break;
case 1:
if(msgSize == 14) {
msgSizeOK = 1;}
break;
case 4:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 6:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 3:
if(msgSize == 2) {
msgSizeOK = 1;}
break;
case 2:
if(msgSize == 2) {
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
