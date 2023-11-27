#include <Arduino.h>
#include "DisplayFunctions.h"

SSD1306AsciiSpi oled;

void setupDisplay() {
  oled.begin(OLED_TYPE, CS_PIN, DC_PIN);
  oled.setFont(OLED_FONT);
  oled.clear();
}

void displayStartupInfo() {
  oled.setCursor(0, 0);
  oled.print(F("Simple DCC-EX Throttle"));
  oled.clearToEOL();
  delay(2000);
  oled.clear();
}

void switchDisplay() {
  if (locoSelect) {
    oled.clear();
    // Display selection menu here
  } else {
    oled.clear();
    displaySpeed();
    displayDirection();
    displayAddress();
  }
}

void displayRuntime() {
  if (locoSelect) {
    // Update selection menu here
  } else {
    if (speedChanged) {
      displaySpeed();
    }
    if (directionChanged) {
      displayDirection();
      directionChanged=false;
    }
  }
}

void displaySpeed() {
  oled.setCursor(40, 0);
  oled.set2X();
  if (selectedLoco) {
    oled.print(selectedLoco->getSpeed());
  } else {
    oled.print(F("0"));
  }
  oled.clearToEOL();
}

void displayDirection() {
  oled.setCursor(30, 3);
  oled.set1X();
  if (selectedLoco) {
    if (selectedLoco->getDirection()==Forward) {
      oled.print(F("Forward"));
    } else {
      oled.print(F("Reverse"));
    }
  } else {
    oled.print(F("---"));
  }  
  oled.clearToEOL();
}

void displayAddress() {
  oled.setCursor(35, 5);
  oled.set1X();
  if (selectedLoco) {
    oled.print(selectedLoco->getAddress());
  } else {
    oled.print(F("0"));
  }
  oled.clearToEOL();
}

void displayMenu() {
  oled.clear();
  int startIdx=menu.getCurrentPage()*menu.getItemsPerPage();
  int row=2;
  for (int i=0; i<menu.getItemsPerPage(); i++) {
    int idx=startIdx + i;
    MenuItem* item=menu.getItemAtIndex(idx);
    if (idx<menu.getItemCount()) {
      oled.setCursor(0, row++);
      oled.print(item->getLocoName());
    }
  }
}

void scrollMenu() {
  
}
