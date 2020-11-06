/////////////////////////////////////////////////////////////////
/*
  UI_Menu.cpp - Tangible CNC UI Main Menu
  Created by Danny Leen, October 17, 2020.
*/
/////////////////////////////////////////////////////////////////


#include "Arduino.h"
#include "Ui_Menu.h"
#include "Free_Fonts.h"

/////////////////////////////////////////////////////////////////

Ui_Menu::Ui_Menu() {
  initScreen();
  //initUiMenu();
}

void Ui_Menu::initScreen() {
    TFT_eSPI tft_ = TFT_eSPI();
    tft_.init();
       if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }
    tft_.setRotation(0);
   
}



void Ui_Menu::initUiMenu() {
  /*Serial.println("fsdfdfsd");
  tft_.init();
  Serial.println("__________");
  tft_.setRotation(0);
  tft_.fillScreen(TFT_BLACK);
  tft_.setTextColor(TFT_WHITE);
  tft_.setCursor(0, 0);
  tft_.setTextDatum(MC_DATUM);
  //
  tft_.drawString("title_", 40, 15);
  Serial.print(title_);*/
   //Ui_Title(_titlePosX, _titlePosY, _title);
  //
  //
//  tft_.setTextColor(TFT_WHITE);
 //   for (int i = 0; i < 3; i++) {
  //    if (i == 0) {
   //     tft_.setFreeFont(FF22);
    //    tft_.fillRoundRect(5, xyzPositionY[i] - 15, tft_.width(), tft_.fontHeight() + 4, 4, TFT_ORANGE);
     //   tft_.drawNumber(xyzValue[i], tft_.width() - 75, xyzPositionY[i]);
      //  tft_.drawString(xyz[i], 20, xyzPositionY[i]);
       // tft_.drawString("mm", tft_.width() - 25, xyzPositionY[i]);
      //}
     // else {
       // tft_.setFreeFont(FF17);
        //tft_.drawNumber(xyzValue[i], 95, xyzPositionY[i]);
        //tft_.drawString(xyz[i], 20, xyzPositionY[i]);
      //}
    //}
}
void Ui_Menu::wait(boolean waiting){
  if (waiting){
     if (moveDot_ < TFT_WIDTH/2){
      tft_.fillCircle(80 +moveDot_, TFT_HEIGHT - 6,  2, TFT_BLACK);
       moveDot_ += 8;
     }
     else{
       tft_.fillRect(0, TFT_HEIGHT - 15, TFT_WIDTH , TFT_HEIGHT , TFT_WHITE);
       moveDot_ = 0;
     }

  }
  else{
  //  tft_.fillRect(0, TFT_HEIGHT - 15, TFT_WIDTH , TFT_HEIGHT , TFT_WHITE);
     moveDot_ = 0;
     setFooter("connected");
  }
}

void Ui_Menu::updateUi() {
    tft_.fillScreen(TFT_BLACK);
    float rectWidth = title_.length() * 15;
    Serial.println(title_.length());
    tft_.fillRoundRect(-20, -10, rectWidth +25 , 40, 8, TFT_GOLD);
    tft_.setTextColor(TFT_WHITE);
    tft_.setTextSize(2);
    tft_.drawString(title_, 10, 8);


    tft_.fillRect(0, TFT_HEIGHT - 15, TFT_WIDTH , TFT_HEIGHT , TFT_WHITE);
    tft_.setTextColor(TFT_BLACK);
    tft_.setTextSize(1);
    Serial.println(text_);
    tft_.drawString(text_, 5, TFT_HEIGHT - 10);
    Serial.println("update");

  //  tft.fillScreen(TFT_BLACK);
  ////  Ui_Title(_titlePosX, _titlePosY, _title);
  //  tft.setTextColor(TFT_WHITE);
  //  for (int i = 0; i < 3; i++) {
  //    if (i == active) {
  //      tft.setFreeFont(FF22);
  //      randomNumber = random(0, 900);
  //      xyzValue[i] = randomNumber;
  //      tft.fillRoundRect(5, xyzPositionY[i] - 15, tft.width(), tft.fontHeight() + 4, 4, TFT_ORANGE);
  //      tft.drawNumber(xyzValue[i], tft.width() - 75, xyzPositionY[i]);
  //      tft.drawString(xyz[i], 20, xyzPositionY[i]);
  //      tft.drawString("mm", tft.width() - 25, xyzPositionY[i]);
  //    }
  //    else {
  //      tft.setFreeFont(FF17);
  //      tft.drawNumber(xyzValue[i], 95, xyzPositionY[i]);
  //      tft.drawString(xyz[i], 20, xyzPositionY[i]);
  //    }
  //  }
  //
  //  tft.setFreeFont(FF0);
  //  String tempString = "G1 X" + String(xyzValue[0]) +  " Y" + String(xyzValue[1]) + " Z" + String(xyzValue[2]) + " F30";
  //  return tempString;
  //  //  firebaseServer.pushDate("/Gcode", tempString);
  //  // tft.drawString(temp, 70, 230);
}

void Ui_Menu::setParameters(){

}


void Ui_Menu::setBlockTypes(FirebaseData &blockData){
     json_ = blockData.jsonObject();
    //Print all object data
}

void Ui_Menu::setBlockType(int blockNmbr){
    
    json_.iteratorBegin();
    String key, value = "";
    int type = 0;
      json_.iteratorGet(blockNmbr, type, key, value);
    //  Serial.print(blockNmbr);
      setTitle(key);
      Serial.println(key);
    json_.iteratorEnd();
}



void Ui_Menu::setFooter(String footerText) {

  text_ = footerText;
  updateUi();

}

void Ui_Menu::setTitle(String title) {

  title_ = title;
  updateUi();

}

void Ui_Menu::setWifiSymbol( int bars){
    for (int b=0; b <= bars; b++) {
        // display.fillRect(59 + (b*5),33 - (b*5),3,b*5,WHITE); 
        tft_.fillRect((TFT_WIDTH -17) + (b*2) ,(TFT_HEIGHT -2) - (b*2),1,b*2,TFT_GREEN); 
      }
 
}

void Ui_Menu::showMenu(int position){
    setTitle("Blocks");
    
    size_t len = json_.iteratorBegin();  
    Serial.println(selected_);

    if(selected_ >= 0 && selected_ <=len -1){
          selected_ += position;
    } 
    if (selected_ == len){
      selected_ = 0;
    }
    if (selected_ < 0){
      selected_ = len -1;
    }

    String key, value = "";
      int type = 0;
      int color;
     for (size_t i = 0; i < len; i++)
     {

      json_.iteratorGet(i, type, key, value);
      if(i == selected_){
          color = TFT_WHITE;
          tempTitle_ = key;
       }else{
          color = TFT_ORANGE;
       }
      tft_.fillRoundRect(5, 40 + (15*i), tft_.width(), tft_.fontHeight() + 4, 4, color);
      tft_.drawString(key, 10, 42 + (15*i));
      
     }
  json_.iteratorEnd();
  

}
void Ui_Menu::closeMenu(){
    setTitle(tempTitle_);
    updateUi();
}
/////////////////////////////////////////////////////////////////
