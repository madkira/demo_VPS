#include "Demo.h"
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

uint8_t timer = 30;


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
  			tft.setRotation(1);
			tft.fillScreen(ST7735_BLACK);
			
Demo_Demo_Reach_Zone_OnEntry(_instance->Demo_Demo_Reach_Zone_State, _instance);
break;
}
case DEMO_DEMO_REACH_ZONE_IDLE_STATE:{

			Score = 0;
			tft.fillScreen(ST7735_BLACK);
		    tar_x = 64;
		    tar_y = 64;
			timer = 30;
			
break;
}
case DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE:{

			tft.fillScreen(ST7735_BLACK);
			tft.setCursor(5, 5);
			    tft.setTextColor(ST7735_YELLOW);
			    tft.setTextSize(2);
			    tft.println("Calibration");
			
break;
}
case DEMO_DEMO_REACH_ZONE_SETPOINT_STATE:{

			tft.fillScreen(ST7735_BLACK);
			tft.setCursor(100,0);
			tft.println(Score);
			tft.drawRect(1, 1, timer*3, 2, ST7735_RED);
			old_x = 0;
			old_y = 0;
			cur_x = 0;
			cur_y = 0;
			tar_x = 5 + random(110);
			tar_y = 5 + random(110);
			
break;
}
case DEMO_DEMO_REACH_ZONE_GAMEOVER_STATE:{

				tft.fillScreen(ST7735_BLACK);
			    tft.setCursor(30, 5);
			    tft.setTextColor(ST7735_YELLOW);
			    tft.setTextSize(3);
			    tft.println("Game\n");
			    tft.setCursor(30, 35);
			    tft.println("Over");
			    tft.setTextColor(ST7735_GREEN);
			    tft.setCursor(50, 70);
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
case DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE:{
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
void Demo_handle_Timer_s1_tic(struct Demo_Instance *_instance) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {

			tft.drawRect(1, 1, timer*3, 2, ST7735_BLACK);
			timer--;
			tft.drawRect(1, 1, timer*3, 2, ST7735_RED);
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
				cur_x = int(x/1000);
				cur_y =128 -  int(y/1000);
				tft.fillCircle(old_x, old_y, DOT, ST7735_BLACK);
			    tft.setCursor(0, 30);
		    	tft.setTextColor(ST7735_YELLOW);
		    	tft.setTextSize(1);
		    	tft.println("   Reach the center");
		    	tft.println("      to Start");
			    tft.drawCircle(tar_x, tar_y, CIRCLE, ST7735_YELLOW);
				tft.fillCircle(cur_x, cur_y, DOT, ST7735_GREEN);
				
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
else if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_SETPOINT_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {

				old_x = cur_x;
				old_y = cur_y;
				cur_x = int(x/1000);
				cur_y = 128 - int(y/1000);
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
void Demo_handle_Output_play(struct Demo_Instance *_instance) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_IDLE_STATE;
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_IDLE_STATE, _instance);
Demo_Demo_Reach_Zone_State_event_consumed = 1;
}
}
//End Region Demo_Reach_Zone
//End dsregion Demo_Reach_Zone
//Session list: 
}
void Demo_handle_Output_calibrating(struct Demo_Instance *_instance) {
if(!(_instance->active)) return;
//Region Demo_Reach_Zone
uint8_t Demo_Demo_Reach_Zone_State_event_consumed = 0;
if (_instance->Demo_Demo_Reach_Zone_State == DEMO_DEMO_REACH_ZONE_IDLE_STATE) {
if (Demo_Demo_Reach_Zone_State_event_consumed == 0 && 1) {
Demo_Demo_Reach_Zone_OnExit(DEMO_DEMO_REACH_ZONE_IDLE_STATE, _instance);
_instance->Demo_Demo_Reach_Zone_State = DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE;
Demo_Demo_Reach_Zone_OnEntry(DEMO_DEMO_REACH_ZONE_CALIBRATION_STATE, _instance);
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
			tft.setCursor(100,0);
			tft.println(Score);
			
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



