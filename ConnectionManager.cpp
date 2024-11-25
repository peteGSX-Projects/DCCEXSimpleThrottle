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
#ifdef WIFI_ENABLED
  _receivedUserSelection = false;
  _selectedCommandStation = 255;
  _commandStationCount = 0;
  _commandStationList = nullptr;
  _wifiStarted = false;
  _wifiRetryDelay = 1000;
  _lastWifiRetry = 0;
  _wifiRetries = 10;
  _serverRetryDelay = 1000;
  _lastServerRetry = 0;
  _serverRetries = 10;
#endif // WIFI_ENABLED
}

void ConnectionManager::update() {
#ifdef WIFI_ENABLED
  if (!_receivedUserSelection)
    return;
  unsigned long currentMillis = millis();
  bool wifiConnected = _connectWiFi(currentMillis);
  bool serverConnected = false;
  if (wifiConnected) {
    serverConnected = _connectServer(currentMillis);
  }
  if (wifiConnected && serverConnected) {
    _connected = true;
  }
#endif // WIFI_ENABLED
}

bool ConnectionManager::connected() { return _connected; }

Stream &ConnectionManager::getConnectionStream() {
#ifdef WIFI_ENABLED
  return _wifiClient;
#else
  return COMMANDSTATION_CONNECTION;
#endif // WIFI_ENABLED
}

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

bool ConnectionManager::_connectWiFi(unsigned long currentMillis) {
  if (WiFi.status() == WL_CONNECTED) {
    _wifiRetries = 10;
    return true;
  }
  if (!_wifiStarted) {
    WiFi.begin(_commandStationList[_selectedCommandStation].ssid,
               _commandStationList[_selectedCommandStation].password);
    _wifiStarted = true;
    return false;
  }
  if ((currentMillis - _lastWifiRetry > _wifiRetryDelay) && _wifiRetries > 0) {
    _lastWifiRetry = currentMillis;
    CONSOLE.print("WiFi connect retries left ");
    CONSOLE.println(_wifiRetries);
    _wifiRetries--;
  }
  return false;
}

bool ConnectionManager::_connectServer(unsigned long currentMillis) {
  if (_wifiClient.connected()) {
    _serverRetries = 10;
    return true;
  }
  if ((currentMillis - _lastServerRetry > _serverRetryDelay) && _serverRetries > 0) {
    CONSOLE.print("Server connect retries left ");
    CONSOLE.println(_serverRetries);
    _lastServerRetry = currentMillis;
    _serverRetries--;
    bool connected = _wifiClient.connect(_commandStationList[_selectedCommandStation].ipAddress,
                                         _commandStationList[_selectedCommandStation].port);
    return connected;
  }
  return false;
}

#endif // WIFI_ENABLED
