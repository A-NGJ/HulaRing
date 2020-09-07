#include <Arduino.h>
#include "utility.hpp"
#include "variables.hpp"

volatile GlobalState globalState = GlobalState::ON_PRESSED;
volatile GlobalState prevGlobalState;
bool bButtonState = 0;
bool bMonoButtonState = 0;
bool bCurrentButtonState = bButtonState;
uint8_t iGlobalState = 0;
uint32_t elapsed_time;
uint32_t time_now;
uint32_t loop_time;
uint32_t switch_time;
uint8_t bDoubleClick;
uint16_t cycle_time;
int intensity[] = {64, 128, 196, 255};
int eco_intensity[] = {32, 64, 96, 128};

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BI_BUTTON_PIN, INPUT);
  pinMode(MONO_BUTTON_PIN, INPUT);
  time_now = millis();
  loop_time = millis();
  switch_time = millis();
  elapsed_time = millis();
  cycle_time = 500;
  attachInterrupt(0, switchMode, CHANGE);
}

void loop() {

  bCurrentButtonState = digitalRead(BI_BUTTON_PIN);
  bMonoButtonState = digitalRead(MONO_BUTTON_PIN);

  if ( millis() - switch_time > cycle_time){
    cycle_time = 500;
    bDoubleClick = 0;
    int* current_intensity = (globalState == GlobalState::ECO) ? eco_intensity : intensity;
    switch(iGlobalState){
      case 0:
        lightLed(current_intensity[0], 10, bCurrentButtonState);
        break;
      case 10:
        lightLed(current_intensity[1], 20, bCurrentButtonState);
        break;
      case 20:
        lightLed(current_intensity[2], 30, bCurrentButtonState);
        break;
      case 30:
        lightLed(current_intensity[3], 0, bCurrentButtonState);
        break;
    }
    switch_time = millis();
  } else {
    prevGlobalState = globalState;
    if ( bDoubleClick == 2) {
      switch( globalState ){
        case GlobalState::ON_PRESSED:
          globalState = GlobalState::CONTINUOUS;
          break;
        case GlobalState::CONTINUOUS:
          globalState = GlobalState::ECO;
          break;
        case GlobalState::ECO:
          globalState = GlobalState::ON_PRESSED;
          break;
      }
      bDoubleClick = 0;
    }
  } 

  if (millis() - time_now > 1000){
    Serial.print("Button State:");
    Serial.println(bButtonState);
    Serial.print("Global State:");
    Serial.println(iGlobalState);
    Serial.print("State: ");
    String print_state;
    switch( globalState ){
      case GlobalState::ON_PRESSED: 
        print_state = "ON_PRESSED";
        break;
      case GlobalState::CONTINUOUS:
        print_state = "CONTINUOUS";
        break;
      case GlobalState::ECO: 
        print_state = "ECO";
        break;
    }
    //  = (globalState == GlobalState::ON_PRESSED) ? "ON_PRESSED" : "CONTINUOUS";
    Serial.println(print_state);
    Serial.print("MONO: ");
    Serial.println(bMonoButtonState);
    time_now = millis();
  }


}
