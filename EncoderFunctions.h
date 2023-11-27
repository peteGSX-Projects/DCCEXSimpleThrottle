#ifndef ENCODERFUNCTIONS_H
#define ENCODERFUNCTIONS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include "defines.h"
#include "avdweb_Switch.h"
#include "Rotary.h"
#include "Menu.h"

extern Rotary encoder;
extern Switch button;
extern bool locoSelect;
extern bool speedChanged;
extern bool directionChanged;
extern Loco* selectedLoco;
extern Menu menu;

void setupButton();
void processEncoder();
void singleClickCallback(void* param);
void doubleClickCallback(void* param);
void longPressCallback(void* param);
void populateMenu();

#endif
