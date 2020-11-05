/////////////////////////////////////////////////////////////////
/*
  ServerCommunication.h - Tangible CNC communicating to Firebase
  Created by Danny Leen, October 17, 2020.
*/
/////////////////////////////////////////////////////////////////

#pragma once

#ifndef ServerCommunication_h
#define ServerCommunication_h


/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "FirebaseESP32.h"
#include "WiFi.h"
#include <SPI.h>
#include "UI/Ui_Menu.h"
//////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////


class ServerCommunication {

  private:
    FirebaseData _firebaseData;
    String _path;

        
  public:
    bool setupWiFi(String wifiSSID, String wifiPassword, Ui_Menu Ui_MenuObj);
    String setupFirebase(String hostNameFireBase, String authKeyFireBase, String path);
    String pushDate(String subPath, String dataToPush);
    String getFireBasePath();
    int getBarsSignal();
};


/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
