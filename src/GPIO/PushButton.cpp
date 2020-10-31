/////////////////////////////////////////////////////////////////
/*
  PushButton.cpp 
  Created by Danny Leen 21 October 2020
*/
/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "PushButton.h"


PushButton::PushButton(byte attachTo, byte buttonMode /*= INPUT_PULLUP*/, unsigned int debounceTimeout /*= DEBOUNCE_MS*/) {
  pin = attachTo;
  setDebounceTime(debounceTimeout);
   Serial.print(pin);
  Serial.println(" inputpull");
  pinMode(attachTo, INPUT_PULLUP);
}

void PushButton::setChangedHandler(CallbackFunction f) {
  change_cb = f; 
}
    
/////////////////////////////////////////////////////////////////

void PushButton::setPressedHandler(CallbackFunction f) {
  pressed_cb = f; 
}

/////////////////////////////////////////////////////////////////

void PushButton::setReleasedHandler(CallbackFunction f) {
  released_cb = f; 
}
        
/////////////////////////////////////////////////////////////////

void PushButton::setClickHandler(CallbackFunction f) {
  click_cb = f;
}

/////////////////////////////////////////////////////////////////

void PushButton::setTapHandler(CallbackFunction f) {
  tap_cb = f;
}

/////////////////////////////////////////////////////////////////

void PushButton::setLongClickHandler(CallbackFunction f) {
  long_cb = f;
}

/////////////////////////////////////////////////////////////////

void PushButton::setDoubleClickHandler(CallbackFunction f) {
  double_cb = f;
}

/////////////////////////////////////////////////////////////////

void PushButton::setTripleClickHandler(CallbackFunction f) {
  triple_cb = f;
}

void PushButton::setDebounceTime(unsigned int ms) {
      debounce_time_ms = ms;
    }
    
boolean PushButton::isPressed() {
  return (state == LOW);
}
    

unsigned int PushButton::getNumberOfClicks() {
    return click_count;
}


unsigned int PushButton::getClickType() {
    return last_click_type;
}

void PushButton::loop() {
  if(pin < 0)return;
  
  prev_state = state;
  state = digitalRead(pin);

  
  // is button pressed?
  if (prev_state == HIGH && state == LOW) {
    down_ms = millis();

    //Serial.println("push");
    pressed_triggered = false;
    click_count++;
    click_ms = down_ms;

  // is the button released?
  } else if (prev_state == LOW && state == HIGH) {
    down_time_ms = millis() - down_ms;
    // is it beyond debounce time?
    if (down_time_ms >= debounce_time_ms) {
       //   Serial.print(pin);
    //Serial.println(": released");
      // trigger release        
  
      // was it a longclick? (preceeds single / double / triple clicks)
      if (down_time_ms >= LONGCLICK_MS) {
        longclick_detected = true;
      }
    }

  // trigger pressed event (after debounce has passed)
  } else if (state == HIGH && !pressed_triggered && (millis() - down_ms >= debounce_time_ms)) {
   
    pressed_triggered = true;
  
  // is the button pressed and the time has passed for multiple clicks?
  }
else if (state == HIGH && millis() - click_ms > DOUBLECLICK_MS) {
    // was there a longclick?
    if (longclick_detected) {
      // was it part of a combination?
      if (click_count == 1) {
        last_click_type = LONG_CLICK;
        //Serial.println("Long click");
        if (long_cb != NULL) long_cb (*this);
      }
      longclick_detected = false;      
    // determine the number of single clicks
    } else if (click_count > 0) {
      switch (click_count) {
        case 1: 
          last_click_type = SINGLE_CLICK;
          //Serial.println("Single click");
          if (click_cb != NULL){
              click_cb (*this);
          } 
          break;
         case 2: 
          last_click_type = DOUBLE_CLICK;
          //Serial.println("Double click");
          if (double_cb != NULL) double_cb (*this);
          break;
         case 3: 
          last_click_type = TRIPLE_CLICK;
          //Serial.println("Triple click");
          if (triple_cb != NULL) triple_cb (*this);
          break;
      }
    }
    click_count = 0;
    click_ms = 0;
  }   
}

/////////////////////////////////////////////////////////////////
