/////////////////////////////////////////////////////////////////
/*
  UI_Menu.h - Tangible CNC UI Main Menu
  Created by Danny Leen, October 17, 2020.
*/
/////////////////////////////////////////////////////////////////

#pragma once

#ifndef Ui_Menu_h
#define Ui_Menu_h


/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include <TFT_eSPI.h>
#include "Free_Fonts.h"

//////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////


class Ui_Menu {

  private:
    String title_;
    String text_;
    int moveDot_ = 0;
    TFT_eSPI tft_ = TFT_eSPI();
    String xyz[3] = {"X:", "Y:", "Z:"};
    int xyzValue[3] = {0, 0, 0};
    boolean xyzFlags[3] = {true, false, false};
    int xyzPositionY[3] = {80, 120, 160};
    int randomNumber;
    void initScreen();
    
    

  public:
    void initUiMenu();
    
    void ui_degrees(int32_t posX, int32_t pos);
    void ui_motor(int32_t posX, int32_t pos);
    void ui_e(int32_t posX, int32_t pos);
    void ui_x(int32_t posX, int32_t pos);
    void ui_y(int32_t posX, int32_t pos);
    void ui_z(int32_t posX, int32_t pos);
    void ui_motorNumber(int32_t posX, int32_t posY);
    void ui_rotate(int32_t posX, int32_t pos);
    void wait(boolean waiting);
    void setWifiSymbol(int bars);
    void setFooter(String footerText);
    Ui_Menu();
    void setTitle(String title);
    void updateUi();
};


/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
