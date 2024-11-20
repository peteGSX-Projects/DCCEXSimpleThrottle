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
#include "StartupScreen.h"

AppOrchestrator::AppOrchestrator(DisplayInterface *displayInterface,
                                 UserConfirmationInterface *userConfirmationInterface,
                                 UserSelectionInterface *userSelectionInterface)
    : _displayInterface(displayInterface), _userConfirmationInterface(userConfirmationInterface),
      _userSelectionInterface(userSelectionInterface) {
  _currentAppState = AppState::STARTUP;
  _tempScreen = new StartupScreen();
}

void AppOrchestrator::begin() {
  _userConfirmationInterface->begin();
  _userSelectionInterface->begin();
  _displayInterface->begin();
}

void AppOrchestrator::update() {
  switch (_currentAppState) {
  case AppState::STARTUP:
    _handleStartupState();
    break;
  case AppState::MENU:
    break;
  case AppState::OPERATION:
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleStartupState() {
  _tempScreen->drawScreen(_displayInterface);
  switch (_userConfirmationInterface->getUserConfirmationAction()) {
  case UserConfirmationAction::SingleClick:
  case UserConfirmationAction::DoubleClick:
  case UserConfirmationAction::LongPress:
    _displayInterface->clear();
  default:
    break;
  }
}

void AppOrchestrator::_handleMenuState() {}

void AppOrchestrator::_handleOperationState() {}
