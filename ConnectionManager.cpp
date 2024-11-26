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
  _wifiMaxRetries = 10;
  _wifiRetry = 1;
  _serverRetryDelay = 1000;
  _lastServerRetry = 0;
  _serverMaxRetries = 10;
  _serverRetry = 1;
  _isConnecting = false;
  _connectionName = nullptr;
  _connectionError = false;
  _connectionErrorMessage = nullptr;
  _retryCounter = 0;
  _newAttempt = false;
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
    _isConnecting = false;
    _connectionError = false;
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
bool ConnectionManager::receivedUserSelection() { return _receivedUserSelection; }

bool ConnectionManager::isConnecting() { return _isConnecting; }

const char *ConnectionManager::getConnectionName() { return _connectionName; }

bool ConnectionManager::connectionError() { return _connectionError; }

const char *ConnectionManager::getConnectionErrorMessage() { return _connectionErrorMessage; }

uint8_t ConnectionManager::getRetryCounter() { return _retryCounter; }

bool ConnectionManager::newAttempt() { return _newAttempt; }

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
}

void ConnectionManager::staticConnectCallback(void *instance, uint8_t commandStationIndex) {
  static_cast<ConnectionManager *>(instance)->selectCommandStation(commandStationIndex);
}

bool ConnectionManager::_connectWiFi(unsigned long currentMillis) {
  if (WiFi.status() == WL_CONNECTED) {
    _wifiRetry = 1;
    return true;
  }
  _connectionName = "Connect WiFi";
  if (!_wifiStarted) {
    WiFi.begin(_commandStationList[_selectedCommandStation].ssid,
               _commandStationList[_selectedCommandStation].password);
    _wifiStarted = true;
    _isConnecting = true;
    return false;
  }
  if ((currentMillis - _lastWifiRetry > _wifiRetryDelay) && _wifiRetry <= _wifiMaxRetries) {
    _lastWifiRetry = currentMillis;
    _retryCounter = _wifiRetry;
    _wifiRetry++;
    _isConnecting = true;
  } else if (_wifiRetry > _wifiMaxRetries && _isConnecting) {
    _connectionError = true;
    _connectionErrorMessage = "WiFi timeout";
    _isConnecting = false;
  }
  return false;
}

bool ConnectionManager::_connectServer(unsigned long currentMillis) {
  if (_wifiClient.connected()) {
    _serverRetry = 1;
    _newAttempt = false;
    return true;
  }
  _connectionName = "Connect CommandStation";
  _newAttempt = true;
  if ((currentMillis - _lastServerRetry > _serverRetryDelay) && _serverRetry <= _serverMaxRetries) {
    _lastServerRetry = currentMillis;
    _retryCounter = _serverRetry;
    _serverRetry++;
    _isConnecting = true;
    bool connected = _wifiClient.connect(_commandStationList[_selectedCommandStation].ipAddress,
                                         _commandStationList[_selectedCommandStation].port);
    return connected;
  } else if (_serverRetry > _serverMaxRetries && _isConnecting) {
    _connectionError = true;
    _connectionErrorMessage = "CommandStation timeout";
    _isConnecting = false;
  }
  return false;
}

#endif // WIFI_ENABLED
