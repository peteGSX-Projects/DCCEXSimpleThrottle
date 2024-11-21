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

#include "AppOrchestrator.h"
#include "OperateScreen.h"
#include "StartupScreen.h"

AppOrchestrator::AppOrchestrator(DisplayInterface *displayInterface,
                                 UserConfirmationInterface *userConfirmationInterface,
                                 UserSelectionInterface *userSelectionInterface)
    : _displayInterface(displayInterface), _userConfirmationInterface(userConfirmationInterface),
      _userSelectionInterface(userSelectionInterface) {
  _currentAppState = AppState::Startup;
  _startupScreen = new StartupScreen();
  _operateScreen = new OperateScreen();
}

void AppOrchestrator::begin() {
  _userConfirmationInterface->begin();
  _userSelectionInterface->begin();
  _displayInterface->begin();
}

void AppOrchestrator::update() {
  switch (_currentAppState) {
  case AppState::Startup:
    _handleStartupState();
    break;
  case AppState::SelectServer:
    _handleSelectServerState();
    break;
  case AppState::SelectLoco:
    _handleSelectLocoState();
    break;
  case AppState::Operate:
    _handleOperateState();
    break;
  case AppState::SelectExtras:
    _handleSelectExtrasState();
    break;
  default:
    break;
  }
}

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

void AppOrchestrator::_handleStartupState() {
  _startupScreen->drawScreen(_displayInterface);
  switch (_userConfirmationInterface->getUserConfirmationAction()) {
  case UserConfirmationAction::SingleClick:
  case UserConfirmationAction::DoubleClick:
  case UserConfirmationAction::LongPress:
    _currentAppState = AppState::Operate;
    _displayInterface->setNeedsRedraw(true);
  default:
    break;
  }
}

void AppOrchestrator::_handleSelectServerState() {}

void AppOrchestrator::_handleSelectLocoState() {}

void AppOrchestrator::_handleOperateState() { _operateScreen->drawScreen(_displayInterface); }

void AppOrchestrator::_handleSelectExtrasState() {}
