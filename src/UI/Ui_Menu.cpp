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
    TFT_eSPI tft = TFT_eSPI();
    tft.init();
       if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }
    tft.setRotation(0);
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(1);
    Serial.println(tft.height());
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
void Ui_Menu::wait(int32_t x, int32_t y, int32_t r){
  tft_.fillCircle(x, y, r, TFT_BLACK);
}

void Ui_Menu::updateUi() {
    tft_.fillScreen(TFT_BLACK);
    tft_.fillRoundRect(-20, -5, tft_.width() , 40, 10, TFT_GOLD);
    tft_.setTextColor(TFT_WHITE);
    tft_.setFreeFont(FF18);
    tft_.drawString(title_, 5, 8);
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


void Ui_Menu::ui_rotate(int posX, int posY) {



}


void Ui_Menu::ui_x(int posX, int posY) {



}


void Ui_Menu::ui_y(int posX, int posY) {



}


void Ui_Menu::ui_z(int posX, int posY) {



}


void Ui_Menu::ui_e(int posX, int posY) {



}


void Ui_Menu::ui_motor(int posX, int posY) {



}



void Ui_Menu::ui_motorNumber(int posX, int posY) {



}



void Ui_Menu::ui_degrees(int posX, int posY) {



}




void Ui_Menu::setTitle(String title) {

  title_ = title;
  updateUi();

}

void Ui_Menu::setText(String text) {
  tft_.fillScreen(TFT_WHITE);
  tft_.setTextColor(TFT_BLACK);
  tft_.drawString(text, 5, TFT_HEIGHT/2);
 // updateUi();

}


/////////////////////////////////////////////////////////////////
