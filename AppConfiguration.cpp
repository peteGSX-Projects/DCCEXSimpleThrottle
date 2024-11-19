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

#include "AppConfiguration.h"

AppConfiguration::AppConfiguration() {
  _userConfirmation = new Button();
  _userSelection = new RotaryEncoder();
  _display = new U8G2SH1106Display();
}

void AppConfiguration::begin() {
  _userConfirmation->begin();
  _userSelection->begin();
  _display->begin();
}

void AppConfiguration::update() {
  UserConfirmationAction action = _userConfirmation->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::SingleClick:
    CONSOLE.println("Single click");
    break;
  case UserConfirmationAction::DoubleClick:
    CONSOLE.println("Double click");
    break;
  case UserConfirmationAction::LongPress:
    CONSOLE.println("Long press");
    break;
  default:
    break;
  }
  UserSelectionAction selection = _userSelection->getUserSelectionAction();
  switch (selection) {
  case UserSelectionAction::Down:
    CONSOLE.println("Down");
    break;
  case UserSelectionAction::Up:
    CONSOLE.println("Up");
    break;
  default:
    break;
  }
}
