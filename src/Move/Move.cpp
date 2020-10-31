/////////////////////////////////////////////////////////////////
/*
  Move.cpp - Tangible CNC UI Main Menu
  Created by Danny Leen, October 17, 2020.
*/
/////////////////////////////////////////////////////////////////


#include "Arduino.h"
#include "UI/Ui_Menu.h"
#include "Move.h"

/////////////////////////////////////////////////////////////////
Move::Move() {
   
  //Serial.println("test");
 // initButtons();
}

void Move::initMove() {
  //initButtons();
}

String Move::getTitle() {
  return "MOVE";
}

void Move::getParameters() {

}

//void Move::initButtons() {
//     
////     UserInputObj.InitButton();
//}

/////////////////////////////////////////////////////////////////
