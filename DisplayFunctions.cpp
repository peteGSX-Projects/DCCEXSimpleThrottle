/*
 *  © 2023 Peter Cole
 *
 *  This file is for a serially connected throttle for a DCC-EX EX-CommandStation.
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"
#include "version.h"

#if defined(OLED_USE_I2C)
OLED oled(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);
#elif defined(OLED_USE_SPI)
OLED oled(U8G2_R0, CS_PIN, DC_PIN);
#endif

void setupDisplay() {
  oled.begin();
  oled.setFont(MENU_FONT);
  oled.clear();
  oled.sendBuffer();
}

void displayStartupInfo() {
  oled.clear();
  oled.setFont(DEFAULT_FONT);
  oled.setCursor(0, 10);
  oled.print(F("Simple DCC-EX Throttle"));
  CONSOLE.print(F("Simple DCC-EX Throttle"));
  oled.setCursor(0, 20);
  oled.print(F("Version: "));
  CONSOLE.print(F(" version: "));
  oled.print(VERSION);
  oled.sendBuffer();
  CONSOLE.println(VERSION);
  delay(2000);
  oled.clear();
  oled.sendBuffer();
}

void switchDisplay() {
  if (locoSelect) {
    displayMenu();
  } else {
    oled.clear();
    oled.sendBuffer();
    oled.setDrawColor(1);
    displaySpeed();
    displayDirection();
    displayLoco();
    displayTrackPower();
  }
}

void displayRuntime() {
  if (!locoSelect) {
    if (speedChanged) {
      displaySpeed();
    }
    if (directionChanged) {
      displayDirection();
      directionChanged=false;
    }
    if (trackPowerChanged) {
      displayTrackPower();
      trackPowerChanged=false;
    }
  }
}

void displaySpeed() {
  oled.setCursor(40, 20);
  oled.setFont(SPEED_FONT);
  oled.print(F("   "));
  oled.setCursor(40, 20);
  if (selectedLoco) {
    oled.print(selectedLoco->getSpeed());
  } else {
    oled.print(F("0"));
  }
  oled.sendBuffer();
}

void displayDirection() {
  oled.setCursor(30, 35);
  oled.setFont(DIRECTION_FONT);
  oled.print(F("       "));
  oled.setCursor(30, 35);
  if (selectedLoco) {
    if (selectedLoco->getDirection()==Forward) {
      oled.print(F("Forward"));
    } else {
      oled.print(F("Reverse"));
    }
  } else {
    oled.print(F("  ---"));
  }  
  oled.sendBuffer();
}

void displayLoco() {
  oled.setCursor(0, 50);
  oled.setFont(ADDRESS_FONT);
  oled.print(F("                      "));
  oled.setCursor(0, 50);
  if (selectedLoco) {
    oled.print(selectedLoco->getName());
  } else {
    oled.print(F("0"));
  }
  oled.sendBuffer();
}

void displayTrackPower() {
  oled.drawHLine(0, 55, 128);
  oled.setCursor(50, 63);
  oled.setFont(MENU_FONT);
  oled.print(F("Track power: "));
  oled.setCursor(112, 63);
  oled.print("   ");
  oled.setCursor(112, 63);
  switch (trackPower) {
    case TrackPower::PowerOff:
      oled.print(F("Off"));
      break;

    case TrackPower::PowerOn:
      oled.print(F("On"));
      break;

    case TrackPower::PowerUnknown:
      oled.print(F("?"));
      break;

    default:
      break;
  }
  oled.sendBuffer();
}

void displayMenu(Menu* menu) {
  oled.clear();
  oled.setDrawColor(1);
  oled.setFont(MENU_FONT);
  oled.drawHLine(0, 7, 128);
  oled.setCursor(0, 6);
  oled.print(F("Select loco"));
  int startIdx=menu.getCurrentPage()*menu.getItemsPerPage();
  int row=11;
  for (int i=0; i<menu.getItemsPerPage(); i++) {
    int idx=startIdx + i;
    LocoMenuItem* item=menu.getItemAtIndex(idx);
    if (idx<menu.getItemCount()) {
      if (idx==selectedMenuItem) {
        oled.setDrawColor(0);
      } else {
        oled.setDrawColor(1);
      }
      oled.drawStr(0, row+=8, item->getLabel());
    }
  }
  oled.sendBuffer();
}

void scrollMenu(int direction) {
  int newIndex=selectedMenuItem+direction;
  int currentPage=menu.getCurrentPage();
  int itemsPP=menu.getItemsPerPage();
  if (newIndex>=0 && newIndex<menu.getItemCount()) {
    selectedMenuItem=newIndex;
    if (selectedMenuItem<currentPage*itemsPP || selectedMenuItem>=(currentPage+1)*itemsPP) {
      currentPage+=direction>0 ? 1 : -1;
      menu.setCurrentPage(currentPage);
    }
    CONSOLE.print(F("selectedMenuItem: "));
    CONSOLE.println(selectedMenuItem);
    displayMenu();
  }  
}

void displayError(const char* error) {
  oled.clear();
  oled.setFont(DEFAULT_FONT);
  oled.setCursor(0, 10);
  oled.print(error);
  oled.setFont(ERROR_FONT);
  oled.drawGlyph(50, 50, 0x0029);
  oled.sendBuffer();
}
