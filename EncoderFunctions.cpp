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
#include "EncoderFunctions.h"
#include "DCCEXFunctions.h"
#include "DisplayFunctions.h"

Rotary encoder(ENCODER_DT, ENCODER_CLK);
Switch button(ENCODER_SW);
bool locoSelect=true;
bool speedChanged=false;
bool directionChanged=false;
Loco* selectedLoco=nullptr;
Menu menu;
int selectedMenuItem=0;
TrackPower trackPower=TrackPower::PowerUnknown;
bool trackPowerChanged=false;

void setupButton() {
  button.setSingleClickCallback(&singleClickCallback, nullptr);
  button.setDoubleClickCallback(&doubleClickCallback, nullptr);
  button.setLongPressCallback(&longPressCallback, nullptr);
}

void processEncoder() {
  unsigned char result=encoder.process();
  if (locoSelect) {
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
  if (locoSelect) {
    MenuItem* selectedItem=menu.getItemAtIndex(selectedMenuItem);
    selectedLoco=selectedItem->getLocoObject();
    locoSelect=false;
    switchDisplay();
  } else {
    if (selectedLoco && selectedLoco->getSpeed()==0) {
      Direction direction=(selectedLoco->getDirection()==Direction::Reverse) ? Direction::Forward : Direction::Reverse;
      dccexProtocol.setThrottle(selectedLoco, selectedLoco->getSpeed(), direction);
    } else if (selectedLoco && selectedLoco->getSpeed()>0) {
      dccexProtocol.setThrottle(selectedLoco, 0, selectedLoco->getDirection());
    }
  }
}

void doubleClickCallback(void* param) {
  CONSOLE.println(F("Double click"));
  if (selectedLoco && selectedLoco->getSpeed()==0 && !locoSelect) {
    locoSelect=true;
    switchDisplay();
  }
}

void longPressCallback(void* param) {
  CONSOLE.println(F("Long press"));
  if (locoSelect) {
    // This should initiate reading loco from prog track
  } else if (selectedLoco && selectedLoco->getSpeed()>0) {
    dccexProtocol.emergencyStop();
  } else if (selectedLoco && selectedLoco->getSpeed()==0) {
    if (trackPower==TrackPower::PowerUnknown || trackPower==TrackPower::PowerOff) {
      dccexProtocol.powerOn();
    } else if (trackPower==TrackPower::PowerOn) {
      dccexProtocol.powerOff();
    }
  }
}
