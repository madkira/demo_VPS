#include "Demo.h"
/*****************************************************************************
 * Implementation for type : Demo
 *****************************************************************************/

// Declaration of prototypes:
//Prototypes: State Machine
void Demo_alpha_OnExit(int state, struct Demo_Instance *_instance);
//Prototypes: Message Sending
void Demo_send_serial1sender_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z);
void Demo_send_serial1sender_noSignal(struct Demo_Instance *_instance);
//Prototypes: Function
// Declaration of functions:

// Sessions functionss:


// On Entry Actions:
void Demo_alpha_OnEntry(int state, struct Demo_Instance *_instance) {
switch(state) {
case DEMO_ALPHA_STATE:{
_instance->Demo_alpha_State = DEMO_ALPHA_IDLE_STATE;
Demo_alpha_OnEntry(_instance->Demo_alpha_State, _instance);
break;
}
case DEMO_ALPHA_IDLE_STATE:{
break;
}
default: break;
}
}

// On Exit Actions:
void Demo_alpha_OnExit(int state, struct Demo_Instance *_instance) {
switch(state) {
case DEMO_ALPHA_STATE:{
Demo_alpha_OnExit(_instance->Demo_alpha_State, _instance);
break;}
case DEMO_ALPHA_IDLE_STATE:{
break;}
default: break;
}
}

// Event Handlers for incoming messages:
void Demo_handle_op_nothing(struct Demo_Instance *_instance) {
if(!(_instance->active)) return;
//Region alpha
uint8_t Demo_alpha_State_event_consumed = 0;
if (_instance->Demo_alpha_State == DEMO_ALPHA_IDLE_STATE) {
if (Demo_alpha_State_event_consumed == 0 && 1) {
Demo_send_serial1sender_noSignal(_instance);
Demo_alpha_State_event_consumed = 1;
}
}
//End Region alpha
//End dsregion alpha
//Session list: 
}
void Demo_handle_op_positionCoordinates(struct Demo_Instance *_instance, double x, double y, double z) {
if(!(_instance->active)) return;
//Region alpha
uint8_t Demo_alpha_State_event_consumed = 0;
if (_instance->Demo_alpha_State == DEMO_ALPHA_IDLE_STATE) {
if (Demo_alpha_State_event_consumed == 0 && 1) {

					uint32_t px = (int)(x*100000);
					uint32_t py = (int)(y*100000);
					uint32_t pz = (int)(z*100000);
					
Demo_send_serial1sender_positionsend(_instance, px, py, pz);
Demo_alpha_State_event_consumed = 1;
}
}
//End Region alpha
//End dsregion alpha
//Session list: 
}

// Observers for outgoing messages:
void (*external_Demo_send_serial1sender_positionsend_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t)= 0x0;
void (*Demo_send_serial1sender_positionsend_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t)= 0x0;
void register_external_Demo_send_serial1sender_positionsend_listener(void (*_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t)){
external_Demo_send_serial1sender_positionsend_listener = _listener;
}
void register_Demo_send_serial1sender_positionsend_listener(void (*_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t)){
Demo_send_serial1sender_positionsend_listener = _listener;
}
void Demo_send_serial1sender_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z){
if (Demo_send_serial1sender_positionsend_listener != 0x0) Demo_send_serial1sender_positionsend_listener(_instance, x, y, z);
if (external_Demo_send_serial1sender_positionsend_listener != 0x0) external_Demo_send_serial1sender_positionsend_listener(_instance, x, y, z);
;
}
void (*external_Demo_send_serial1sender_noSignal_listener)(struct Demo_Instance *)= 0x0;
void (*Demo_send_serial1sender_noSignal_listener)(struct Demo_Instance *)= 0x0;
void register_external_Demo_send_serial1sender_noSignal_listener(void (*_listener)(struct Demo_Instance *)){
external_Demo_send_serial1sender_noSignal_listener = _listener;
}
void register_Demo_send_serial1sender_noSignal_listener(void (*_listener)(struct Demo_Instance *)){
Demo_send_serial1sender_noSignal_listener = _listener;
}
void Demo_send_serial1sender_noSignal(struct Demo_Instance *_instance){
if (Demo_send_serial1sender_noSignal_listener != 0x0) Demo_send_serial1sender_noSignal_listener(_instance);
if (external_Demo_send_serial1sender_noSignal_listener != 0x0) external_Demo_send_serial1sender_noSignal_listener(_instance);
;
}



