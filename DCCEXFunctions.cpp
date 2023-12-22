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
#include "DCCEXFunctions.h"
#include "defines.h"

DCCEXProtocol dccexProtocol;
DCCEXCallbacks dccexCallbacks;

uint8_t connectionRetries=CONNECT_RETRIES;
unsigned long retryDelay=1000;
unsigned long lastRetry=0;
bool gotRoster=false;
bool retrievalDisplayed=false;
bool errorDisplayed=false;
bool setupScreen=false;
int col=0;
int row=2;

void getRoster() {
  if (!dccexProtocol.receivedLists() && connectionRetries>0) {
    if (!retrievalDisplayed) {
      oled.clear();
      oled.setCursor(0, 0);
      oled.print(F("Retrieving roster..."));
      CONSOLE.print(F("Retrieving roster..."));
      retrievalDisplayed=true;
    } else if (!dccexProtocol.receivedLists() && millis()-lastRetry>retryDelay && connectionRetries>0) {
      lastRetry=millis();
      connectionRetries--;
      oled.setCursor(col, row);
      oled.print(F("."));
      CONSOLE.print(F("."));
      col=col+5;
      if (col>120) {
        row++;
        col=0;
      }
    }
    dccexProtocol.getLists(true, false, false, false);
  } else if (!dccexProtocol.receivedLists() && connectionRetries==0 && !errorDisplayed) {
    oled.clear();
    oled.setCursor(0, 0);
    oled.print(F("Could not retrieve roster"));
    CONSOLE.println(F("\nCould not retrieve roster"));
    errorDisplayed=true;
  } else if (dccexProtocol.receivedLists() && !setupScreen) {
    setupScreen=true;
    CONSOLE.println(F("Roster retrieved"));
    populateMenu();
  }
}

void populateMenu() {
  if (dccexProtocol.roster->getFirst()) {
    for (Loco* r=dccexProtocol.roster->getFirst(); r; r=r->getNext()) {
      currentMenu->addItem(new LocoMenuItem(r));
      CONSOLE.println(r->getName());
    }
  }
  switchDisplay();
}

void togglePower() {
  if (trackPower==TrackPower::PowerUnknown || trackPower==TrackPower::PowerOff) {
    dccexProtocol.powerOn();
  } else if (trackPower==TrackPower::PowerOn) {
    dccexProtocol.powerOff();
  }
  if (selectedLoco) {
    encoderMode=OPERATE_LOCO;
    menuDisplay=false;
    switchDisplay();
  } else {
    currentMenu=&rosterMenu;
    encoderMode=SELECT_LOCO;
    menuDisplay=true;
    switchDisplay();
  }
}

void forgetLoco() {
  if (selectedLoco->getSource()==LocoSourceEntry) {
    delete(selectedLoco);
  }
  selectedLoco=nullptr;
  currentMenu=&rosterMenu;
  encoderMode=SELECT_LOCO;
  menuDisplay=true;
  switchDisplay();
}
