#include <Arduino.h>

#ifndef VARIABLES
#define VARIABLES

#define LED_PIN 5
#define BI_BUTTON_PIN 2
#define MONO_BUTTON_PIN 8

enum class GlobalState {
    ON_PRESSED,
    CONTINUOUS,
    ECO
};

extern int intensity[];
extern int eco_intensity[]; 

extern bool bButtonState;
extern bool bCurrentButtonState;
extern bool bMonoButtonState;
volatile extern GlobalState globalState;
volatile extern GlobalState prevGlobalState;
extern uint8_t bDoubleClick;
extern uint8_t iGlobalState;
extern uint32_t time_now;
extern uint32_t loop_time;
extern uint32_t switch_time;
extern uint32_t elapsed_time;
extern uint16_t cycle_time;

#endif
