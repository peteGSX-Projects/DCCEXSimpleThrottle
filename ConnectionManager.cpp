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
  _commandStationCount = 0;
  _commandStationList = nullptr;
}

void ConnectionManager::update() {}

#ifdef WIFI_ENABLED
void ConnectionManager::setCommandStationList(CommandStationDetails *commandStationList, uint8_t commandStationCount) {
  _commandStationCount = commandStationCount;
  _commandStationList = commandStationList;
}

void ConnectionManager::connectWiFi(uint8_t commandStationIndex) {
  if (!_commandStationList)
    return;
  CONSOLE.print("Connect to CS index ");
  CONSOLE.println(commandStationIndex);
  CONSOLE.print("Connect to WiFi SSID|Password: ");
  CONSOLE.print(_commandStationList[commandStationIndex].ssid);
  CONSOLE.print("|");
  CONSOLE.println(_commandStationList[commandStationIndex].password);
}

void ConnectionManager::staticConnectCallback(void *instance, uint8_t commandStationIndex) {
  static_cast<ConnectionManager *>(instance)->connectWiFi(commandStationIndex);
}

#endif // WIFI_ENABLED
