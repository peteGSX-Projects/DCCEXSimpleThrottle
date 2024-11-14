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

#ifndef DCCEXFUNCTIONS_H
#define DCCEXFUNCTIONS_H

#include "DCCEXCallbacks.h"
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Create the dccexProtocol object for all CommandStation interactions
extern DCCEXProtocol dccexProtocol;

/// @brief Create the callback/delegate object to respond to broadcasts and responses
extern DCCEXCallbacks dccexCallbacks;

/// @brief Function to retrieve the roster information
void getRoster();

/// @brief Function to populate the menu with roster entries
void populateMenu();

/// @brief Function to toggle the current track power state
void togglePower();

/// @brief Function to forget the currently selected loco
void forgetLoco();

#endif
