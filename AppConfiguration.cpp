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
  _userConfirmationInterface = new Button();
  _userSelectionInterface = new RotaryEncoder();
  _displayInterface = new U8G2SH1106Display();
  _appOrchestrator = new AppOrchestrator(_displayInterface, _userConfirmationInterface, _userSelectionInterface);
}

void AppConfiguration::initialise() {}

UserConfirmationInterface *AppConfiguration::getUserConfirmationInterface() { return _userConfirmationInterface; }

UserSelectionInterface *AppConfiguration::getUserSelectionInterface() { return _userSelectionInterface; }

DisplayInterface *AppConfiguration::getDisplayInterface() { return _displayInterface; }

AppOrchestrator *AppConfiguration::getAppOrechstrator() { return _appOrchestrator; }

// void AppConfiguration::update() {
//   UserConfirmationAction action = _userConfirmation->getUserConfirmationAction();
//   switch (action) {
//   case UserConfirmationAction::SingleClick:
//     CONSOLE.println("Single click");
//     break;
//   case UserConfirmationAction::DoubleClick:
//     CONSOLE.println("Double click");
//     break;
//   case UserConfirmationAction::LongPress:
//     CONSOLE.println("Long press");
//     break;
//   default:
//     break;
//   }
//   UserSelectionAction selection = _userSelection->getUserSelectionAction();
//   switch (selection) {
//   case UserSelectionAction::Down:
//     CONSOLE.println("Down");
//     break;
//   case UserSelectionAction::Up:
//     CONSOLE.println("Up");
//     break;
//   default:
//     break;
//   }
// }
