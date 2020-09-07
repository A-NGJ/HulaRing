#include <Arduino.h>

#ifndef UTILITY
#define UTILITY

bool isButtonPressed();
void lightLed(uint8_t brightness, uint8_t global_state, uint16_t elapsed_time=500);
void switchMode();

#endif