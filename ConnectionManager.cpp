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

#include "ConnectionManager.h"

ConnectionManager::ConnectionManager() {
  _connected = false;
  _receivedUserSelection = false;
  _selectedCommandStation = 255;
  _commandStationCount = 0;
  _commandStationList = nullptr;
  _wifiRetryDelay = 1000;
  _lastWifiRetry = 0;
  _wifiRetries = 10;
  _serverRetryDelay = 1000;
  _lastServerRetry = 0;
  _serverRetries = 10;
}

void ConnectionManager::update() {
  _connectWiFi();
  _connectServer();
}

bool ConnectionManager::connected() { return _connected; }

#ifdef WIFI_ENABLED
void ConnectionManager::setCommandStationList(CommandStationDetails *commandStationList, uint8_t commandStationCount) {
  _commandStationCount = commandStationCount;
  _commandStationList = commandStationList;
}

void ConnectionManager::selectCommandStation(uint8_t commandStationIndex) {
  if (!_commandStationList)
    return;
  if (commandStationIndex >= _commandStationCount)
    return;
  _receivedUserSelection = true;
  _selectedCommandStation = commandStationIndex;
  CONSOLE.print("Connect to CS index|WiFi SSID|Password: ");
  CONSOLE.print(_selectedCommandStation);
  CONSOLE.print("|");
  CONSOLE.print(_commandStationList[commandStationIndex].ssid);
  CONSOLE.print("|");
  CONSOLE.println(_commandStationList[commandStationIndex].password);
}

void ConnectionManager::staticConnectCallback(void *instance, uint8_t commandStationIndex) {
  static_cast<ConnectionManager *>(instance)->selectCommandStation(commandStationIndex);
}

void ConnectionManager::_connectWiFi() {}

void ConnectionManager::_connectServer() {}

#endif // WIFI_ENABLED
