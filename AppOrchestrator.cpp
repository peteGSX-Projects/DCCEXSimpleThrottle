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
                                 UserSelectionInterface *userSelectionInterface, ThrottleScreen *throttleScreen)
    : _displayInterface(displayInterface), _connectionManager(connectionManager), _menuManager(menuManager),
      _commandStationClient(commandStationClient), _userConfirmationInterface(userConfirmationInterface),
      _userSelectionInterface(userSelectionInterface), _throttleScreen(throttleScreen) {
  _currentAppState = AppState::Startup;
  _startupScreen = new StartupScreen();
  _errorScreen = new ErrorScreen();
  _progressScreen = new ProgressScreen();
}

void AppOrchestrator::begin() {}

void AppOrchestrator::update() {
  if (_connectionManager) {
#ifdef WIFI_ENABLED
    _connectionManager->update();
    if (_connectionManager->isConnecting() && _currentAppState != AppState::ConnectCommandStation) {
      _switchState(AppState::ConnectCommandStation);
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
#else
    if (!_commandStationClient->isConnected()) {
      Stream *connectionStream = _connectionManager->getConnectionStream();
      if (connectionStream) {
        _commandStationClient->setConnectionStream(connectionStream);
      }
    } else {
      _commandStationClient->update();
    }
#endif // WIFI_ENABLED
  }
  switch (_currentAppState) {
  case AppState::Startup:
    _handleStartupState();
    break;
  case AppState::SelectCommandStation:
    _handleSelectCommandStationState();
    break;
  case AppState::ConnectCommandStation:
    _handleConnectCommandStationState();
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
  case AppState::ReadLocoAddress:
    _handleReadLocoState();
  default:
    break;
  }
}

void AppOrchestrator::onEvent(Event &event) {
  switch (event.eventType) {
  case EventType::CommandStationSelected: {
#ifdef WIFI_ENABLED
    if (_connectionManager) {
      _connectionManager->selectCommandStation(event.eventData.byteValue);
    }
#endif // WIFI_ENABLED
    break;
  }
  case EventType::ReceivedRosterList: {
    setupSelectLocoMenu();
    break;
  }
  case EventType::LocoSelected: {
    setThrottleLoco(event.eventData.locoValue);
    break;
  }
  case EventType::ReadLocoAddress: {
    _readLoco();
    break;
  }
  case EventType::ReceivedReadLoco: {
    _handleReceivedReadLoco(event.eventData.intValue);
    break;
  }
  case EventType::ReceivedLocoBroadcast: {
    updateThrottleLoco(event.eventData.locoBroadcastValue);
    break;
  }
  case EventType::ReceivedTrackPower: {
    updateThrottleTrackPower(event.eventData.trackPowerValue);
    break;
  }
  case EventType::JoinProgTrack: {
    _handleJoinProgTrack();
    break;
  }
  case EventType::SetPowerMain:
  case EventType::SetPowerProg: {
    _handleSetTrackPower(event);
    break;
  }
  default: {
    CONSOLE.print("AppOrchestrator received unknown event ");
    CONSOLE.println(event.eventType);
    break;
  }
  }
}

void AppOrchestrator::setupSelectLocoMenu() {
  if (_commandStationClient && _commandStationClient->isConnected()) {
    DCCEXProtocol *dccexClient = _commandStationClient->getClient();
    Loco *firstRosterLoco = dccexClient->roster->getFirst();
    if (firstRosterLoco) {
      _menuManager->setupLocoMenu(firstRosterLoco);
      _displayInterface->setNeedsMenuRefresh(true);
    }
  }
}

void AppOrchestrator::setThrottleLoco(Loco *loco) {
  if (_throttleScreen) {
    _throttleScreen->setLoco(loco);
    _switchState(AppState::Throttle);
  }
}

void AppOrchestrator::updateThrottleLoco(LocoBroadcast locoBroadcast) {
  if (_throttleScreen) {
    _throttleScreen->locoBroadcastReceived(locoBroadcast);
  }
}

void AppOrchestrator::updateThrottleTrackPower(TrackPower trackPower) {
  if (_throttleScreen) {
    _throttleScreen->trackPowerUpdateReceived(trackPower);
  }
}

void AppOrchestrator::_handleStartupState() {
  _startupScreen->drawScreen(_displayInterface);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::SingleClick:
  case UserConfirmationAction::DoubleClick:
  case UserConfirmationAction::LongPress:
    _switchState(AppState::SelectCommandStation);
    break;
  default:
    break;
  }
}

void AppOrchestrator::_handleSelectCommandStationState() {
  if (!_menuManager)
    return;
#ifdef WIFI_ENABLED
  SelectCommandStationMenu *menu = _menuManager->getSelectCommandStationMenu();
  if (!menu)
    return;
  _displayMenu(menu);
  menu->handleUserSelectionAction(_userSelectionInterface->getUserSelectionAction());
  menu->handleUserConfirmationAction(_userConfirmationInterface->getUserConfirmationAction());
  if (_connectionManager) {
    if (_connectionManager->receivedUserSelection()) {
      _switchState(AppState::ConnectCommandStation);
    }
  }
#endif // WIFI_ENABLED
}

void AppOrchestrator::_handleConnectCommandStationState() {
  if (!_progressScreen)
    return;
#ifdef WIFI_ENABLED
  if (_connectionManager->newAttempt()) {
    _displayInterface->setNeedsRedraw(true);
  }
  _progressScreen->setActivity(_connectionManager->getConnectionName());
  _progressScreen->setCounter(_connectionManager->getRetryCounter());
  _progressScreen->drawScreen(_displayInterface);
  if (_connectionManager->connected()) {
    _switchState(AppState::SelectLoco);
  }
#endif // WIFI_ENABLED
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
  if (_displayInterface->needsRedraw()) {
    _throttleScreen->requestLocoUpdate();
    _throttleScreen->requestTrackPowerUpdate();
  }
  _throttleScreen->drawScreen(_displayInterface);
  UserConfirmationAction action = _userConfirmationInterface->getUserConfirmationAction();
  switch (action) {
  case UserConfirmationAction::DoubleClick: {
    if (_throttleScreen->getSpeed() == 0) {
      _switchState(AppState::SelectLoco);
    } else {
      _throttleScreen->handleUserConfirmationAction(action);
    }
    break;
  }
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
#ifdef WIFI_ENABLED
  _errorScreen->setErrorMessage(_connectionManager->getConnectionErrorMessage());
  _errorScreen->drawScreen(_displayInterface);
#endif // WIFI_ENABLED
}

void AppOrchestrator::_switchState(AppState appState) {
  _displayInterface->setNeedsRedraw(true);
  switch (appState) {
  case AppState::Startup:
    _currentAppState = AppState::Startup;
    break;
  case AppState::Throttle:
    _currentAppState = AppState::Throttle;
    break;
  case AppState::SelectAction:
    _currentAppState = AppState::SelectAction;
    break;
  case AppState::SelectLoco:
    _currentAppState = AppState::SelectLoco;
    break;
  case AppState::SelectCommandStation:
    _currentAppState = AppState::SelectCommandStation;
    break;
  case AppState::ConnectCommandStation:
    _currentAppState = AppState::ConnectCommandStation;
    break;
  case AppState::Error:
    _currentAppState = AppState::Error;
    break;
  case AppState::ReadLocoAddress:
    _currentAppState = AppState::ReadLocoAddress;
    break;
  default:
    break;
  }
}

void AppOrchestrator::_displayMenu(BaseMenu *menu) {
  MenuScreen menuScreen(menu);
  menuScreen.drawScreen(_displayInterface);
}

void AppOrchestrator::_handleJoinProgTrack() {
  _commandStationClient->joinProgTrack();
  _switchState(AppState::SelectLoco);
}

void AppOrchestrator::_handleSetTrackPower(Event event) {
  _commandStationClient->setTrackPower(event);
  _switchState(AppState::SelectLoco);
}

void AppOrchestrator::_readLoco() {
  if (_commandStationClient->isConnected()) {
    _commandStationClient->getClient()->readLoco();
    _switchState(AppState::ReadLocoAddress);
  }
}

void AppOrchestrator::_handleReadLocoState() {
  if (!_progressScreen)
    return;
  _progressScreen->setActivity("Reading Loco address");
  _progressScreen->setCounter(15);
  _progressScreen->drawScreen(_displayInterface);
}

void AppOrchestrator::_handleReceivedReadLoco(int address) {
  if (address == -1 || address == 0) {
    _switchState(AppState::SelectLoco);
  } else {
    Loco *readLoco = nullptr;
    for (Loco *roster = _commandStationClient->getClient()->roster->getFirst(); roster; roster = roster->getNext()) {
      if (roster->getAddress() == address) {
        readLoco = roster;
        break;
      }
    }
    if (!readLoco) {
      readLoco = new Loco(address, LocoSource::LocoSourceEntry);
      // Get length of address
      int addressLength = (address == 0) ? 1 : log10(abs(address)) + 1;
      // Create a buffer for address + null terminator
      char *nameBuffer = new char[addressLength + 1];
      // Convert to string and set the name
      itoa(address, nameBuffer, 10);
      readLoco->setName(nameBuffer);
      delete[] nameBuffer;
    }
    setThrottleLoco(readLoco);
  }
}
