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
    path_ = path;
    Firebase.begin(hostNameFireBase, authKeyFireBase);
    Firebase.reconnectWiFi(true);
    return  "Succes";
  }
  else {
    return  "Wifi Connection error";
  }
  
  return "";
}




String ServerCommunication::pushDate(String subPath, String dataToPush) {
  if (Firebase.setString(firebaseData, path_ + subPath, dataToPush))
  {
    return "Succes";
    //tft.setTextColor(TFT_GREEN);
    //tft.drawString("Succes!", 70, 230);
  }
  else
  {
    return "Failed - Reason: " + firebaseData.errorReason();

  }
  return "";
}



String ServerCommunication::getFireBasePath() {
  return path_;
}


bool ServerCommunication::getConfigFirebase(){
    if (Firebase.get(firebaseData,  path_ + "/Config"))
        {   
            Serial.println("Got config files");
            printResult(firebaseData);               
            Serial.println("------------------------------------");
            Serial.println();
            return true;
        }
        else
        {
            Serial.println("Failed");
            Serial.println("Reason: " + firebaseData.errorReason());
            Serial.println("------------------------------------");
            Serial.println();
            return false;
        }

}

bool ServerCommunication::getModulesFirebase(){
    if (Firebase.getShallowData(firebaseData,  path_ + "/Modules"))
        {   
            Serial.println("Got Modules");
            Serial.println("PATH: " + firebaseData.dataPath());
            Serial.println("TYPE: " + firebaseData.dataType());
           // printResult(firebaseData);               
            Serial.println("------------------------------------");
            return true;
        }
        else
        {
            Serial.println("Failed");
            Serial.println("Reason: " + firebaseData.errorReason());
            Serial.println("------------------------------------");
            return false;
        }

}

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
void ServerCommunication::printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_FLOAT)
        Serial.println(jsonData.floatValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
               jsonData.typeNum == FirebaseJson::JSON_NULL ||
               jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData.typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
  else if (data.dataType() == "blob")
  {

    Serial.println();

    for (int i = 0; i < data.blobData().size(); i++)
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      if (i < 16)
        Serial.print("0");

      Serial.print(data.blobData()[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  else if (data.dataType() == "file")
  {

    Serial.println();

    File file = data.fileStream();
    int i = 0;

    while (file.available())
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      int v = file.read();

      if (v < 16)
        Serial.print("0");

      Serial.print(v, HEX);
      Serial.print(" ");
      i++;
    }
    Serial.println();
    file.close();
  }
  else
  {
    Serial.println(data.payload());
  }
}
