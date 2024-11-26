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
  _commandStationClient = new DCCEXProtocol();
}

void CommandStationClient::begin() {
  if (_logStream) {
    _commandStationClient->setLogStream(_logStream);
  }
  if (_commandStationListener) {
    _commandStationClient->setDelegate(_commandStationListener);
  }
}

void CommandStationClient::update() { _commandStationClient->check(); }
