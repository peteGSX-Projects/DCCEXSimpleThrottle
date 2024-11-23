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
#include "MenuScreen.h"
#include "OperateScreen.h"
#include "StartupScreen.h"

AppOrchestrator::AppOrchestrator(DisplayInterface *displayInterface, MenuManager *menuManager,
                                 UserConfirmationInterface *userConfirmationInterface,
                                 UserSelectionInterface *userSelectionInterface)
    : _displayInterface(displayInterface), _menuManager(menuManager),
      _userConfirmationInterface(userConfirmationInterface), _userSelectionInterface(userSelectionInterface) {
  _currentAppState = AppState::Startup;
  _startupScreen = new StartupScreen();
  _operateScreen = new OperateScreen();
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
  case AppState::SelectAction:
    _handleSelectActionState();
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleStartupState() {
  _startupScreen->drawScreen(_displayInterface);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::SingleClick:
  case UserConfirmationAction::DoubleClick:
  case UserConfirmationAction::LongPress:
    _switchState(AppState::SelectServer);
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleSelectServerState() {
  if (!_menuManager)
    return;
  auto *menu = _menuManager->getSelectServerMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  UserSelectionAction selection = _userSelectionInterface->getUserSelectionAction();
  menu->handleUserSelectionAction(selection);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick:
  case UserConfirmationAction::LongPress:
    break;
  case UserConfirmationAction::SingleClick:
    _switchState(AppState::SelectLoco);
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleSelectLocoState() {
  if (!_menuManager)
    return;
  auto *menu = _menuManager->getSelectLocoMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::LongPress:
    break;
  case UserConfirmationAction::SingleClick:
    _switchState(AppState::Operate);
    break;
  case UserConfirmationAction::DoubleClick:
    _switchState(AppState::SelectAction);
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleOperateState() {
  _operateScreen->drawScreen(_displayInterface);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick:
    if (_operateScreen->getSpeed() == 0) {
      _switchState(AppState::SelectLoco);
    } else {
      _operateScreen->handleUserConfirmationAction(action);
    }
    break;
  default:
    _operateScreen->handleUserConfirmationAction(action);
    _operateScreen->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction(),
                                              _userSelectionInterface->throttleInverted());
    break;
  }
}

void AppOrchestrator::_handleSelectActionState() {
  if (!_menuManager)
    return;
  auto *menu = _menuManager->getSelectActionMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::LongPress:
    break;
  case UserConfirmationAction::SingleClick:
    _switchState(AppState::Operate);
    break;
  case UserConfirmationAction::DoubleClick:
    _switchState(AppState::SelectLoco);
    break;
  default:
    break;
  }
}

void AppOrchestrator::_switchState(AppState appState) {
  _displayInterface->setNeedsRedraw(true);
  switch (appState) {
  case AppState::Startup:
    _currentAppState = AppState::Startup;
    break;
  case AppState::Operate:
    _currentAppState = AppState::Operate;
    break;
  case AppState::SelectAction:
    _currentAppState = AppState::SelectAction;
    break;
  case AppState::SelectLoco:
    _currentAppState = AppState::SelectLoco;
    break;
  case AppState::SelectServer:
    _currentAppState = AppState::SelectServer;
    break;
  default:
    break;
  }
}

void AppOrchestrator::_displayMenu(BaseMenu *menu) {
  MenuScreen menuScreen(menu);
  if (menu->getSelectionChanged()) {
    _displayInterface->setNeedsRedraw(true);
  }
  menuScreen.drawScreen(_displayInterface);
}
