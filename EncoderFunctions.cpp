#include <Arduino.h>
#include "EncoderFunctions.h"
#include "DCCEXFunctions.h"

Rotary encoder(ENCODER_DT, ENCODER_CLK);
Switch button(ENCODER_SW);
bool locoSelect=false;
bool speedChanged=false;
bool directionChanged=false;
Loco* selectedLoco=nullptr;
Menu menu;

void setupButton() {
  button.setSingleClickCallback(&singleClickCallback, nullptr);
  button.setDoubleClickCallback(&doubleClickCallback, nullptr);
  button.setLongPressCallback(&longPressCallback, nullptr);
}

void processEncoder() {
  unsigned char result=encoder.process();
  if (locoSelect) {
    // Selection menu here
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
    }
  }
  button.poll();
}

void singleClickCallback(void* param) {
  if (locoSelect) {
    // Selection menu here
  } else {
    if (selectedLoco && selectedLoco->getSpeed()==0) {
      Direction direction=(direction==Direction::Reverse) ? Direction::Forward : Direction::Reverse;
      directionChanged=true;
    }
  }
}

void doubleClickCallback(void* param) {

}

void longPressCallback(void* param) {

}

void populateMenu() {
  for (Loco* r=dccexProtocol.roster->getFirst(); r; r=r->getNext()) {
    MenuItem* newItem=new MenuItem(r->getName(), r);
    menu.addItem(newItem);
  }
}
