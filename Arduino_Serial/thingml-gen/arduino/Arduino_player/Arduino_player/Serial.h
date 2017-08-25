#ifndef __Serial__
#define __Serial__
#include <stdint.h>
#include <Arduino.h>
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
#endif