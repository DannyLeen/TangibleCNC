/////////////////////////////////////////////////////////////////
/*
  ServerCommunication.cpp - Tangible CNC communicating to Firebase
  Created by Danny Leen, October 17, 2020.
*/
/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "ServerCommunication.h"
#include <SPI.h>
#include "WiFi.h"
//#include "FirebaseESP32.h"
////////////////////////////////////////////////////////////


bool ServerCommunication::setupWiFi(String wifiSSID, String wifiPassword, Ui_Menu Ui_MenuObj) {
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  Serial.print("Connecting to Wi-Fi");
  int move = 0;
  while (WiFi.status() != WL_CONNECTED)
  {

    Ui_MenuObj.wait(20 + move,80, 5);
    Serial.print(".");
    delay(300);
    move +=15;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    Ui_MenuObj.setText(String(WiFi.localIP()));
     delay(5000);
    return true;
  }
  else {
    Serial.print("Connection error");
    return false;
  }

}

////////////////////////////////////////////////////////////

String ServerCommunication::setupFirebase(String hostNameFireBase, String authKeyFireBase, String path) {
  
 if (WiFi.status() == WL_CONNECTED) {
    _path = path;
    Firebase.begin(hostNameFireBase, authKeyFireBase);
    Firebase.reconnectWiFi(true);
    return  "Succes";
  }
  else {
    return  "Wifi Connection error";
  }
  
  return "";
}

////////////////////////////////////////////////////////////


String ServerCommunication::pushDate(String subPath, String dataToPush) {
  if (Firebase.setString(_firebaseData, _path + subPath, dataToPush))
  {
    return "Succes";
    //tft.setTextColor(TFT_GREEN);
    //tft.drawString("Succes!", 70, 230);
  }
  else
  {
    return "Failed - Reason: " + _firebaseData.errorReason();

  }
  return "";
}

/////////////////////////////////////////////////////////////////

String ServerCommunication::getFireBasePath() {
  return _path;
}

/////////////////////////////////////////////////////////////////
