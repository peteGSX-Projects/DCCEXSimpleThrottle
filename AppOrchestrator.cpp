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

AppOrchestrator::AppOrchestrator(DisplayInterface *displayInterface, ConnectionManager *connectionManager,
                                 MenuManager *menuManager, CommandStationClient *commandStationClient,
                                 UserConfirmationInterface *userConfirmationInterface,
                                 UserSelectionInterface *userSelectionInterface)
    : _displayInterface(displayInterface), _connectionManager(connectionManager), _menuManager(menuManager),
      _commandStationClient(commandStationClient), _userConfirmationInterface(userConfirmationInterface),
      _userSelectionInterface(userSelectionInterface) {
  _currentAppState = AppState::Startup;
  _startupScreen = new StartupScreen();
  _throttleScreen = new ThrottleScreen(THROTTLE_STEP, THROTTLE_STEP_FASTER, THROTTLE_STEP_FASTEST);
  _errorScreen = new ErrorScreen();
  _progressScreen = new ProgressScreen();
}

void AppOrchestrator::begin() {}

void AppOrchestrator::update() {
  if (_connectionManager) {
    _connectionManager->update();
    if (_connectionManager->isConnecting() && _currentAppState != AppState::ConnectServer) {
      _switchState(AppState::ConnectServer);
    } else if (_connectionManager->connectionError() && _currentAppState != AppState::Error) {
      _switchState(AppState::Error);
    } else if (_connectionManager->connected()) {
      if (!_commandStationClient->isConnected()) {
        Stream *connectionStream = _connectionManager->getConnectionStream();
        if (connectionStream) {
          _commandStationClient->setConnectionStream(connectionStream);
          CONSOLE.println("Connecting to CS");
        }
      } else {
        _commandStationClient->update();
      }
    }
  }
  switch (_currentAppState) {
  case AppState::Startup:
    _handleStartupState();
    break;
  case AppState::SelectServer:
    _handleSelectServerState();
    break;
  case AppState::ConnectServer:
    _handleConnectServerState();
    break;
  case AppState::SelectLoco:
    _handleSelectLocoState();
    break;
  case AppState::Throttle:
    _handleThrottleState();
    break;
  case AppState::SelectAction:
    _handleSelectActionState();
    break;
  case AppState::Error:
    _handleErrorState();
    break;
  default:
    break;
  }
}

void AppOrchestrator::setupSelectLocoMenu() {
  if (_commandStationClient && _commandStationClient->isConnected()) {
    Loco *firstLoco = _commandStationClient->getFirstRosterEntry();
    if (firstLoco) {
      _menuManager->setupLocoMenu(firstLoco);
      _displayInterface->setNeedsMenuRefresh(true);
    }
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
  SelectServerMenu *menu = _menuManager->getSelectServerMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  menu->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction());
  menu->handleUserConfirmationAction(_userConfirmationInterface->getUserConfirmationAction());
  if (_connectionManager) {
    if (_connectionManager->receivedUserSelection()) {
      _switchState(AppState::ConnectServer);
    }
  }
}

void AppOrchestrator::_handleConnectServerState() {
  if (!_progressScreen)
    return;
  if (_connectionManager->newAttempt()) {
    _displayInterface->setNeedsRedraw(true);
  }
  _progressScreen->setActivity(_connectionManager->getConnectionName());
  _progressScreen->setCounter(_connectionManager->getRetryCounter());
  _progressScreen->drawScreen(_displayInterface);
  if (_connectionManager->connected()) {
    _switchState(AppState::SelectLoco);
  }
}

void AppOrchestrator::_handleSelectLocoState() {
  if (!_menuManager)
    return;
  SelectLocoMenu *menu = _menuManager->getSelectLocoMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  menu->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction());
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick:
    _switchState(AppState::SelectAction);
    break;
  default:
    menu->handleUserConfirmationAction(action);
    break;
  }
}

void AppOrchestrator::_handleThrottleState() {
  _throttleScreen->drawScreen(_displayInterface);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick:
    if (_throttleScreen->getSpeed() == 0) {
      _switchState(AppState::SelectLoco);
    } else {
      _throttleScreen->handleUserConfirmationAction(action);
    }
    break;
  default:
    _throttleScreen->handleUserConfirmationAction(action);
    _throttleScreen->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction(),
                                               _userSelectionInterface->throttleInverted());
    break;
  }
}

void AppOrchestrator::_handleSelectActionState() {
  if (!_menuManager)
    return;
  SelectActionMenu *menu = _menuManager->getSelectActionMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  menu->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction());
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick:
    _switchState(AppState::SelectLoco);
    break;
  default:
    menu->handleUserConfirmationAction(action);
    break;
  }
}

void AppOrchestrator::_handleErrorState() {
  if (!_errorScreen)
    return;
  _errorScreen->setErrorMessage(_connectionManager->getConnectionErrorMessage());
  _errorScreen->drawScreen(_displayInterface);
}

void AppOrchestrator::_switchState(AppState appState) {
  _displayInterface->setNeedsRedraw(true);
  switch (appState) {
  case AppState::Startup:
    CONSOLE.println("Switch to AppState::Startup");
    _currentAppState = AppState::Startup;
    break;
  case AppState::Throttle:
    CONSOLE.println("Switch to AppState::Throttle");
    _currentAppState = AppState::Throttle;
    break;
  case AppState::SelectAction:
    CONSOLE.println("Switch to AppState::SelectAction");
    _currentAppState = AppState::SelectAction;
    break;
  case AppState::SelectLoco:
    CONSOLE.println("Switch to AppState::SelectLoco");
    _currentAppState = AppState::SelectLoco;
    break;
  case AppState::SelectServer:
    CONSOLE.println("Switch to AppState::SelectServer");
    _currentAppState = AppState::SelectServer;
    break;
  case AppState::ConnectServer:
    CONSOLE.println("Switch to AppState::ConnectServer");
    _currentAppState = AppState::ConnectServer;
    break;
  case AppState::Error:
    CONSOLE.println("Switch to AppState::Error");
    _currentAppState = AppState::Error;
    break;
  default:
    break;
  }
}

void AppOrchestrator::_displayMenu(BaseMenu *menu) {
  MenuScreen menuScreen(menu);
  menuScreen.drawScreen(_displayInterface);
}
