
#include <Arduino.h>
#include "TangibleCNC.h"

#include <AceButton.h>
using namespace ace_button;


 // Invoke custom library
TangibleCNC TangibleCNCObj("T10 V2.0");


// The pin number attached to the button.
int btnPinNmbrs[3] = {36,37,39};
AceButton buttons[3];
void handleEvent(AceButton*, uint8_t, uint8_t);



void setup()
{    
  TangibleCNCObj.Ui_MenuObj.setTitle("INIT");
  Serial.begin(115200);
  delay(1000);
for (uint8_t i = 0; i < 3; i++) {
    // initialize built-in LED as an output
    pinMode(btnPinNmbrs[i], INPUT);
    buttons[i].init(btnPinNmbrs[i], HIGH, i);
}
  
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(handleEvent);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
  TangibleCNCObj.Ui_MenuObj.setFooter("Connecting");
  TangibleCNCObj.setWiFi("telenet-58366", "jypJ7tmsphaj");
  //TangibleCNCObj.setWiFi("Fablab_5G", NULL);
  TangibleCNCObj.setFirebase("m5stack-8f1cb.firebaseio.com", "Z6dFnfN4dnhdYkJBFHHr8abNpGHHlbt7lUZGOmTo", "/Maak-Machines");
  TangibleCNCObj.Ui_MenuObj.setTitle("Rotate");
  TangibleCNCObj.Ui_MenuObj.setFooter("All Good");
}

void loop()
{
// tft.fillScreen(TFT_BLACK);

 // tft_.fillScreen(TFT_BLACK);

    TangibleCNCObj.loop();
    for (uint8_t i = 0; i < 3; i++) {
           buttons[i].check();
  }

}

// The event handler for the button.
void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.print(F("id:  "));
  Serial.println(button->getId());
  // Print out a message for all events.
  Serial.print(F("handleEvent(): eventType: "));
  Serial.print(eventType);
  Serial.print(F("; buttonState: "));
  Serial.println(buttonState);
}