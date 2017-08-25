#ifndef __timer2__
#define __timer2__
#include <stdint.h>
#include <Arduino.h>

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

#endif