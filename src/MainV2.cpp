
#include <Arduino.h>
#include "TangibleCNC.h"





 // Invoke custom library
TangibleCNC TangibleCNCObj("T10 V2.0");

void setup()
{    
  Serial.begin(115200);
  delay(1000);

  TangibleCNCObj.setWiFi("telenet-58366", "jypJ7tmsphaj");
  //TangibleCNCObj.setWiFi("Fablab_5G", NULL);
  TangibleCNCObj.setFirebase("m5stack-8f1cb.firebaseio.com", "Z6dFnfN4dnhdYkJBFHHr8abNpGHHlbt7lUZGOmTo", "/Maak-Machines");
  TangibleCNCObj.setBlockType("Move");
  //Serial.println("Set");

}

void loop()
{
// tft.fillScreen(TFT_BLACK);

 // tft_.fillScreen(TFT_BLACK);

  //  TangibleCNCObj.loop();
  delay(50);
}
