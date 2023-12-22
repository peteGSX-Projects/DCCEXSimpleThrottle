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
#include "defines.h"
#include "EncoderFunctions.h"
#include "DCCEXFunctions.h"
#include "DisplayFunctions.h"
#include "DeviceFunctions.h"

Rotary encoder(ENCODER_DT, ENCODER_CLK);
Switch button(ENCODER_SW);
bool menuDisplay=true;
bool speedChanged=false;
bool directionChanged=false;
Loco* selectedLoco=nullptr;
Menu rosterMenu("Select loco");
Menu serverMenu("Select server");
Menu extrasMenu("Select action");
Menu* currentMenu=nullptr;
int selectedMenuItem=0;
TrackPower trackPower=TrackPower::PowerUnknown;
bool trackPowerChanged=false;
EncoderMode encoderMode;

void setupButton() {
  button.setSingleClickCallback(&singleClickCallback, nullptr);
  button.setDoubleClickCallback(&doubleClickCallback, nullptr);
  button.setLongPressCallback(&longPressCallback, nullptr);
}

void processEncoder() {
  unsigned char result=encoder.process();
  if (menuDisplay) {
    if (result==DIR_CW) {
      scrollMenu(1);
    } else if (result==DIR_CCW) {
      scrollMenu(-1);
    }
  } else {
    if (selectedLoco) {
      int speed=selectedLoco->getSpeed();
      if (result==DIR_CW && speed<126) {
        speed++;
        speedChanged=true;
      } else if (result==DIR_CCW && speed>0) {
        speed--;
        speedChanged=true;
      } else {
        speedChanged=false;
      }
      if (speedChanged) {
        dccexProtocol.setThrottle(selectedLoco, speed, selectedLoco->getDirection());
      }
    }
  }
  button.poll();
}

void singleClickCallback(void* param) {
  CONSOLE.println(F("Single click"));
  switch(encoderMode) {
    case OPERATE_LOCO: {
      if (selectedLoco && selectedLoco->getSpeed()==0) {
        Direction direction=(selectedLoco->getDirection()==Direction::Reverse) ? Direction::Forward : Direction::Reverse;
        dccexProtocol.setThrottle(selectedLoco, selectedLoco->getSpeed(), direction);
      } else if (selectedLoco && selectedLoco->getSpeed()>0) {
        dccexProtocol.setThrottle(selectedLoco, 0, selectedLoco->getDirection());
      }
      break;
    }

#if defined(ARDUINO_ARCH_ESP32)
    case SELECT_SERVER: {
      MenuItem* selectedItem=currentMenu->getItemAtIndex(selectedMenuItem);
      setupWiFi(selectedItem->getIndex());
      if (connected) {
        encoderMode=SELECT_LOCO;
        currentMenu=&rosterMenu;
        switchDisplay();
      }
      break;
    }
#endif

    case SELECT_LOCO: {
      MenuItem* selectedItem=currentMenu->getItemAtIndex(selectedMenuItem);
      if (LocoMenuItem* locoItem=static_cast<LocoMenuItem*>(selectedItem)) {
        selectedLoco=locoItem->getLocoObject();
        encoderMode=OPERATE_LOCO;
        menuDisplay=false;
        switchDisplay();
      }
      break;
    }

    case SELECT_EXTRAS: {
      MenuItem* selectedItem=currentMenu->getItemAtIndex(selectedMenuItem);
      if (ActionMenuItem* actionItem=static_cast<ActionMenuItem*>(selectedItem)) {
        actionItem->callAction();
      }
      break;
    }

    default:
      break;
  }
}

void doubleClickCallback(void* param) {
  CONSOLE.println(F("Double click"));
  switch(encoderMode) {
    case OPERATE_LOCO: {
      if (selectedLoco && selectedLoco->getSpeed()==0 && !menuDisplay) {
        menuDisplay=true;
        currentMenu=&rosterMenu;
        encoderMode=SELECT_LOCO;
        switchDisplay();
      }
      break;
    }

    case SELECT_LOCO: {
      menuDisplay=true;
      currentMenu=&extrasMenu;
      encoderMode=SELECT_EXTRAS;
      switchDisplay();
      break;
    }

    case SELECT_EXTRAS: {
      menuDisplay=true;
      currentMenu=&rosterMenu;
      encoderMode=SELECT_LOCO;
      switchDisplay();
      break;
    }

    default:
      break;
  }
  
}

void longPressCallback(void* param) {
  CONSOLE.println(F("Long press"));
  switch(encoderMode) {
    case OPERATE_LOCO: {
      if (selectedLoco && selectedLoco->getSpeed()>0) {
        dccexProtocol.emergencyStop();
      }
      break;
    }

    default:
      break;
  }
}
