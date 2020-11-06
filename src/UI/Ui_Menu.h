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
#include "FirebaseESP32.h"

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
    FirebaseJson json_;
    int selected_;
    String tempTitle_;
    
  public:
    Ui_Menu();
    void initUiMenu();
  

    void wait(boolean waiting);
    void setWifiSymbol(int bars);
    void setFooter(String footerText);
    void setTitle(String title);
    void updateUi();
    void setBlockTypes(FirebaseData &blockData);
    void setBlockType(int nmbr);
    void showMenu(int selected);
    void closeMenu();
    void setParameters();
};


/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
