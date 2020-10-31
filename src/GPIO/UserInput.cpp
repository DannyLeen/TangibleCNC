/////////////////////////////////////////////////////////////////
/*
  GPIO.cpp - Tangible CNC UI GPIO
  Created by Danny Leen, October 19, 2020.
*/
/////////////////////////////////////////////////////////////////


#include "Arduino.h"
#include "UserInput.h"
/////////////////////////////////////////////////////////////////

bool btnClick1 = false;
bool btnClick2 = false;
bool btnClick3 = false;
bool btnClick4 = false;

UserInput::UserInput(): _btn1(36,  INPUT), _btn2(37, INPUT), _btn3(39, INPUT)   {

  _btn1.setClickHandler([](PushButton & b) {
    btnClick1 = true;
  });
  _btn2.setClickHandler([](PushButton & b) {
    btnClick2 = true;
  });
  _btn3.setClickHandler([](PushButton & b) {
    btnClick3 = true;
  });


}
void UserInput::confirm(int btnNumber)
{
  Serial.print(btnNumber);
  Serial.println(" confirm");
}

void UserInput::loop()
{
  _btn1.loop();

  if (btnClick1) {
    confirm(1);
    btnClick1 = false;
  }
  _btn2.loop();
  if (btnClick2) {
    confirm(2);
    btnClick2 = false;
  }
  _btn3.loop();
  if (btnClick3) {
    confirm(3);
    btnClick3 = false;
  }

}
/////////////////////////////////////////////////////////////////
