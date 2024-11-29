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

#ifdef WIFI_ENABLED
  _commandStationCount = COMMANDSTATION_COUNT;
  _initialiseCommandStationArray();
#endif // WIFI_ENABLED

  _eventManager = new EventManager();
  _connectionManager = new ConnectionManager();
  _menuManager = new MenuManager(_eventManager);
  _commandStationListener = new CommandStationListener(_eventManager);
  _commandStationClient = new CommandStationClient(&CONSOLE, _commandStationListener);
  _appOrchestrator = new AppOrchestrator(_displayInterface, _connectionManager, _menuManager, _commandStationClient,
                                         _userConfirmationInterface, _userSelectionInterface);
}

void AppConfiguration::initialise() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  _disableJTAG();
#endif // BLUEPILL
  _userConfirmationInterface->begin();
  _userSelectionInterface->begin();
  _displayInterface->begin();
#ifdef WIFI_ENABLED
  _menuManager->setupServerMenu(_commandStationList, _commandStationCount);
  _connectionManager->setCommandStationList(_commandStationList, _commandStationCount);
#endif // WIFI_ENABLED
  _registerEvents();
  _commandStationClient->begin();
}

UserConfirmationInterface *AppConfiguration::getUserConfirmationInterface() { return _userConfirmationInterface; }

UserSelectionInterface *AppConfiguration::getUserSelectionInterface() { return _userSelectionInterface; }

DisplayInterface *AppConfiguration::getDisplayInterface() { return _displayInterface; }

AppOrchestrator *AppConfiguration::getAppOrchestrator() { return _appOrchestrator; }

ConnectionManager *AppConfiguration::getConnectionManager() { return _connectionManager; }

MenuManager *AppConfiguration::getMenuManager() { return _menuManager; }

CommandStationClient *AppConfiguration::getCommandStationClient() { return _commandStationClient; }

void AppConfiguration::_registerEvents() {
  _eventManager->registerEvent("SelectedCommandStation", EventManager::staticSelectCommandStation, _connectionManager);
  _eventManager->registerEvent("ReceivedRosterList", EventManager::staticReceivedRosterList, _appOrchestrator);
  _eventManager->registerEvent("SelectedLoco", EventManager::staticSelectLoco, _appOrchestrator);
  _eventManager->registerEvent("ReceivedLocoUpdate", EventManager::staticReceivedLocoUpdate, _appOrchestrator);
}

#ifdef WIFI_ENABLED
void AppConfiguration::_initialiseCommandStationArray() {
  const char *csNames[] = COMMANDSTATION_NAMES;         // array to store names of CommandStations
  const char *csIPs[] = COMMANDSTATION_IPS;             // array to store IPs of CommandStations
  const uint16_t csPorts[] = COMMANDSTATION_PORTS;      // array to store ports of CommandStations
  const char *csSSIDs[] = COMMANDSTATION_SSIDS;         // array to store SSIDs of CommandStations
  const char *csPasswords[] = COMMANDSTATION_PASSWORDS; // array to store passwords of CommandStations

  for (uint8_t i = 0; i < _commandStationCount; i++) {
    _commandStationList[i].name = csNames[i];
    _commandStationList[i].ipAddress = _convertIP(csIPs[i]);
    _commandStationList[i].port = csPorts[i];
    _commandStationList[i].ssid = csSSIDs[i];
    _commandStationList[i].password = csPasswords[i];
  }
}

IPAddress AppConfiguration::_convertIP(const char *ipAddressString) {
  int first;
  int second;
  int third;
  int fourth;
  if (sscanf(ipAddressString, "%d.%d.%d.%d", &first, &second, &third, &fourth) == 4) {
    if ((first >= 0 && first <= 255) && (second >= 0 && second <= 255) && (third >= 0 && third <= 255) &&
        (fourth >= 0 && fourth <= 255)) {
      return IPAddress(first, second, third, fourth);
    } else {
      CONSOLE.println("IP address is out of range");
    }
  } else {
    CONSOLE.println("Invalid IP address format");
  }
  return IPAddress(0, 0, 0, 0);
}
#endif // WIFI_ENABLED

#if defined(ARDUINO_BLUEPILL_F103C8)
void AppConfiguration::_disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}
#endif // BLUEPILL
