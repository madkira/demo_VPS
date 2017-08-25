#ifndef __Serial1__
#define __Serial1__
#include "WProgram.h"
/*****************************************************/
//                    Serial1
/*****************************************************/
struct Serial1_instance_type {
    uint16_t listener_id;
    //Connector
};
extern struct Serial1_instance_type Serial1_instance;

void Serial1_setup();

void Serial1_set_listener_id(uint16_t id);

void Serial1_forwardMessage(byte * msg, uint8_t size);

void Serial1_read();

/********************* FORWARDERS *********************/

/*FORWARDERS*/// Forwarding of messages Serial1::Demo::serial1sender::positionsend
void forward_Serial1_Demo_send_serial1sender_positionsend(struct Demo_Instance *_instance, uint32_t x, uint32_t y, uint32_t z);
// Forwarding of messages Serial1::Demo::serial1sender::noSignal
void forward_Serial1_Demo_send_serial1sender_noSignal(struct Demo_Instance *_instance);

#endif