
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
boolean menuShown = false;

void setup()
{    
  TangibleCNCObj.Ui_MenuObj.setTitle("Init");
  Serial.begin(115200);
  delay(1000);
for (uint8_t i = 0; i < 3; i++) {
    pinMode(btnPinNmbrs[i], INPUT);
    buttons[i].init(btnPinNmbrs[i], HIGH, i);
    }
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(handleEvent);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  TangibleCNCObj.Ui_MenuObj.setFooter("Connecting");
  TangibleCNCObj.setWiFi("telenet-58366", "jypJ7tmsphaj");
  //TangibleCNCObj.setWiFi("Fablab_5G", NULL);
  TangibleCNCObj.setFirebase("m5stack-8f1cb.firebaseio.com", "Z6dFnfN4dnhdYkJBFHHr8abNpGHHlbt7lUZGOmTo", "/Maak-Machines");
  //TangibleCNCObj.getConfigFirebase();
  TangibleCNCObj.getModulesFirebase();
  TangibleCNCObj.Ui_MenuObj.setFooter("All Good");
}

void loop()
{
    TangibleCNCObj.loop();
    for (uint8_t i = 0; i < 3; i++) {
           buttons[i].check();
  }
}
// The event handler for the button.
void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  int id  = button->getId();
  if (id  == 0 && eventType == 4){
      if( menuShown==false){
            TangibleCNCObj.Ui_MenuObj.showMenu(0);
            menuShown = true;
      }
      else{
           menuShown = false;
          TangibleCNCObj.Ui_MenuObj.closeMenu();
      }
  }
  if (menuShown == true &&  id  == 1 && eventType == 1 && buttonState == 1){
      TangibleCNCObj.Ui_MenuObj.showMenu(-1);
  }
  if (menuShown == true && id  == 2  && eventType == 1 && buttonState == 1){
      TangibleCNCObj.Ui_MenuObj.showMenu(+1);
  }
}