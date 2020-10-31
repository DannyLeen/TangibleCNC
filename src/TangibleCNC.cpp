/////////////////////////////////////////////////////////////////
/*
  TangibleCNC.cpp - Tangible CNC main class
  Created by Danny Leen, October 19, 2020.
*/
/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "TangibleCNC.h"
#include "GPIO/PushButton.h"

////////////////////////////////////////////////////////////

TangibleCNC::TangibleCNC(String firmware){
  Serial.begin(115200);
  Serial.println(firmware);
  Move MoveObj;
 // UserInput UserInputObj;
  //Ui_MenuObj.initUiMenu();  
}

bool TangibleCNC::setWiFi(String wifiSSID, String wifiPassword) {
  return ServerCommunicationObj.setupWiFi(wifiSSID, wifiPassword, Ui_MenuObj);
}


bool TangibleCNC::setFirebase(String hostName, String authKey, String path) {
  return ServerCommunicationObj.setupFirebase(hostName,  authKey, path);
}


bool  TangibleCNC::setBlockType(String Type) {
  
  if (Type == "Move") {
    Ui_MenuObj.setTitle( MoveObj.getTitle());
    Serial.println(MoveObj.getTitle());
    // Ui_MenuObj.setParameters(MoveObj.getParameters());
    return true;
  }
  else if (Type == "Rotate") {
    Ui_MenuObj.setTitle("ROTATE");
    return true;
  }
  else {
    return false;
  }

}

void TangibleCNC::screenUpdate() {
  Ui_MenuObj.updateUi();
}

void TangibleCNC::loop() {
  Ui_MenuObj.updateUi();
  //  MoveObj.Loop();
  UserInputObj.loop();
}