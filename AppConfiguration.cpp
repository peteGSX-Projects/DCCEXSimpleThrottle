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
  _menuManager = new MenuManager();
  _appOrchestrator =
      new AppOrchestrator(_displayInterface, _menuManager, _userConfirmationInterface, _userSelectionInterface);
}

void AppConfiguration::initialise() {
  _userConfirmationInterface->begin();
  _userSelectionInterface->begin();
  _displayInterface->begin();
}

UserConfirmationInterface *AppConfiguration::getUserConfirmationInterface() { return _userConfirmationInterface; }

UserSelectionInterface *AppConfiguration::getUserSelectionInterface() { return _userSelectionInterface; }

DisplayInterface *AppConfiguration::getDisplayInterface() { return _displayInterface; }

AppOrchestrator *AppConfiguration::getAppOrchestrator() { return _appOrchestrator; }

MenuManager *AppConfiguration::getMenuManager() { return _menuManager; }
