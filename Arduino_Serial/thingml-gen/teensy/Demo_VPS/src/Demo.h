#ifndef __Demo__
#define __Demo__
#include "WProgram.h"
/*****************************************************************************
 * Headers for type : Demo
 *****************************************************************************/

// Definition of the instance struct:
struct Demo_Instance {

// Instances of different sessions
bool active;
// Variables for the ID of the ports of the instance
uint16_t id_op;
uint16_t id_serial1sender;
// Variables for the current instance state
int Demo_alpha_State;
// Variables for the properties of the instance

};
// generateEventHandlers2
int Demo_handle_empty_event(struct Demo_Instance *_instance);
// Declaration of prototypes outgoing messages :
void Demo_alpha_OnEntry(int state, struct Demo_Instance *_instance);
void Demo_handle_op_endvalidate(struct Demo_Instance *_instance);
void Demo_handle_op_positionCoordinates(struct Demo_Instance *_instance, double x, double y, double z);
void Demo_handle_op_nothing(struct Demo_Instance *_instance);
void Demo_handle_op_calibrate(struct Demo_Instance *_instance);
// Declaration of callbacks for incoming messages:
void register_Demo_send_serial1sender_positionsend_listener(void (*_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t));
void register_external_Demo_send_serial1sender_positionsend_listener(void (*_listener)(struct Demo_Instance *, uint32_t, uint32_t, uint32_t));
void register_Demo_send_serial1sender_noSignal_listener(void (*_listener)(struct Demo_Instance *));
void register_external_Demo_send_serial1sender_noSignal_listener(void (*_listener)(struct Demo_Instance *));
void register_Demo_send_serial1sender_calibrating_listener(void (*_listener)(struct Demo_Instance *));
void register_external_Demo_send_serial1sender_calibrating_listener(void (*_listener)(struct Demo_Instance *));
void register_Demo_send_serial1sender_play_listener(void (*_listener)(struct Demo_Instance *));
void register_external_Demo_send_serial1sender_play_listener(void (*_listener)(struct Demo_Instance *));

// Definition of the states:
#define DEMO_ALPHA_STATE 0
#define DEMO_ALPHA_IDLE_STATE 1



#endif