/*
 *  © 2024 Peter Cole
 *  © 2023 Peter Cole
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

#include "Defines.h"
#include "Menu.h"
#include "Rotary.h"
#include "avdweb_Switch.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

extern Rotary encoder;          // object for the rotary encoder
extern Switch button;           // object for the rotary encoder's button
extern bool menuDisplay;        // flag for if the menu should be displayed or not
extern bool speedChanged;       // flag if loco speed has changed
extern bool directionChanged;   // flag if loco direction has changed
extern Loco *selectedLoco;      // pointer to the currently selected loco
extern Menu rosterMenu;         // object for the menu of roster entries
extern Menu serverMenu;         // object for the menu of user defined CommandStations
extern Menu extrasMenu;         // object for extra menu items accessible via double click
extern Menu *currentMenu;       // pointer to the currently active menu
extern int selectedMenuItem;    // index of the currently selected menu item
extern TrackPower trackPower;   // enum of the current track power state
extern bool trackPowerChanged;  // flag if track power state has changed
extern EncoderMode encoderMode; // enum of the current mode for the rotary encoder

/// @brief Initial configuration of the rotary encoder button's callback methods
void setupButton();

/// @brief Check the state of the rotary encoder and either scroll menu items or change loco speed
void processEncoder();

/// @brief Actions to perform when single clicking the rotary encoder button:
/// - Reverse direction if loco is stopped
/// - Send a normal stop if loco is moving
/// - Select a menu item if a menu is display
/// @param param Set to nullptr, unused in this implementation
void singleClickCallback(void *param);

/// @brief Actions to perform when double clicking the rotary encoder button:
/// - Switch from loco display to roster menu
/// - Switch from roter menu to extras menu
/// - Switch from extras menu to roster menu
/// @param param Set to nullptr, unused in this implementation
void doubleClickCallback(void *param);

/// @brief When operating a loco, send emergency stop
/// @param param Set to nullptr, unused in this implementation
void longPressCallback(void *param);

#endif
