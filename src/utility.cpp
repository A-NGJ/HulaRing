#include "utility.hpp"
#include "variables.hpp"


bool isButtonPressed(){
  if( bCurrentButtonState != bButtonState ){
    bButtonState = !bButtonState;
    return true;
  }
  return false;
}

void lightLed(uint8_t brightness, uint8_t global_state, uint16_t elapsed_time=500){
  Serial.println(bMonoButtonState);
  if ((globalState == GlobalState::ON_PRESSED && bMonoButtonState == 1) 
       || (globalState == GlobalState::CONTINUOUS)
       || (globalState == GlobalState::ECO))
    analogWrite(LED_PIN, brightness);
  else
    analogWrite(LED_PIN, 0);
  if (isButtonPressed() && millis() - loop_time > elapsed_time){
    iGlobalState = global_state;
    loop_time = millis();
  }
}

void switchMode(){
    if(millis() - elapsed_time > 60){
        cycle_time = (cycle_time == 500) ? 1000 : cycle_time;
        bDoubleClick++;
        Serial.println(bDoubleClick);
        elapsed_time = millis();
    }
}
