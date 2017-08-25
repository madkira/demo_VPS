#ifndef __Demo__
#define __Demo__
#include <stdint.h>
#include <Arduino.h>
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



#endif