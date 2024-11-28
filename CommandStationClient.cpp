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

#include "CommandStationClient.h"

CommandStationClient::CommandStationClient(Stream *logStream, CommandStationListener *commandStationListener)
    : _logStream(logStream), _commandStationListener(commandStationListener) {
  _connectionStream = nullptr;
  _commandStationClient = new DCCEXProtocol();
  _isConnected = false;
  _rosterMaxRetries = 10;
  _rosterRetry = 1;
  _lastRosterRetry = 0;
  _rosterRetryDelay = 1000;
}

void CommandStationClient::begin() {
  if (_logStream) {
    _commandStationClient->setLogStream(_logStream);
  }
  if (_commandStationListener) {
    _commandStationClient->setDelegate(_commandStationListener);
  }
}

void CommandStationClient::setConnectionStream(Stream *connectionStream) {
  _connectionStream = connectionStream;
  if (_connectionStream) {
    _commandStationClient->connect(_connectionStream);
    _isConnected = true;
  } else {
    _isConnected = false;
  }
}

void CommandStationClient::update() {
  if (!_isConnected)
    return;
  _commandStationClient->check();
  if (!_commandStationClient->receivedLists()) {
    unsigned long currentMillis = millis();
    if ((currentMillis - _lastRosterRetry > _rosterRetryDelay) && (_rosterRetry <= _rosterMaxRetries)) {
      _lastRosterRetry = currentMillis;
      _rosterRetry++;
      _commandStationClient->getLists(true, false, false, false);
    }
  }
}

bool CommandStationClient::isConnected() { return _isConnected; }

Loco *CommandStationClient::getFirstRosterEntry() {
  if (_isConnected) {
    return _commandStationClient->roster->getFirst();
  }
  return nullptr;
}
