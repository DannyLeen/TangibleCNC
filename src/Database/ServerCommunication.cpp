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
  while (WiFi.status() != WL_CONNECTED)
  {

    Ui_MenuObj.wait(true);
    Serial.print(".");
    delay(300);
  }
  if (WiFi.status() == WL_CONNECTED) {

    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
   // Ui_MenuObj.setText(String(WiFi.localIP()));
     //delay(5000);
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
int ServerCommunication::getBarsSignal(){
  // 5. High quality: 90% ~= -55db
  // 4. Good quality: 75% ~= -65db
  // 3. Medium quality: 50% ~= -75db
  // 2. Low quality: 30% ~= -85db
  // 1. Unusable quality: 8% ~= -96db
  // 0. No signal
  long rssi = WiFi.RSSI();
  int bars;
  
  if (rssi > -55) { 
    bars = 5;
  } else if (rssi < -55 && rssi > -65) {
    bars = 4;
  } else if (rssi < -65 && rssi > -75) {
    bars = 3;
  } else if (rssi < -75 && rssi > -85) {
    bars = 2;
  } else if (rssi < -85 && rssi > -96) {
    bars = 1;
  } else {
    bars = 0;
  }
  return bars;
}