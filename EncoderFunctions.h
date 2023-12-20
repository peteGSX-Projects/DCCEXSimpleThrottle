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

#ifndef ENCODERFUNCTIONS_H
#define ENCODERFUNCTIONS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include "avdweb_Switch.h"
#include "Rotary.h"
#include "Menu.h"

extern Rotary encoder;
extern Switch button;
extern bool menuDisplay;
extern bool speedChanged;
extern bool directionChanged;
extern Loco* selectedLoco;
extern Menu rosterMenu;
extern Menu serverMenu;
extern Menu extrasMenu;
extern Menu* currentMenu;
extern int selectedMenuItem;
extern TrackPower trackPower;
extern bool trackPowerChanged;

void setupButton();
void processEncoder();
void singleClickCallback(void* param);
void doubleClickCallback(void* param);
void longPressCallback(void* param);

#endif
