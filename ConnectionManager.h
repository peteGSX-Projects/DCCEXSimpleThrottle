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

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "CommandStationDetails.h"
#include "Defines.h"

#ifdef WIFI_ENABLED
#include <WiFi.h>
#endif // WIFI_ENABLED

class ConnectionManager {
public:
  /// @brief Constructor for the ConnectionManager
  ConnectionManager();

  /// @brief Managed all connections, reconnect if necessary
  void update();

  /// @brief Check if connections are active
  /// @return True|False
  bool connected();

  /// @brief Get the connect stream managed by this ConnectionManager
  /// @return Stream object
  Stream &getConnectionStream();

#ifdef WIFI_ENABLED
  /// @brief Set the list of CommandStations
  /// @param commandStationList Pointer to the array of CommandStations
  /// @param commandStationCount Count of CommandStations
  void setCommandStationList(CommandStationDetails *commandStationList, uint8_t commandStationCount);

  /// @brief Select the CommandStation to connect to
  /// @param commandStationIndex Index of the list of CommandStationDetails to connect to
  void selectCommandStation(uint8_t commandStationIndex);

  /// @brief Wrapper method to enable callbacks to call connection methods
  /// @param instance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  static void staticConnectCallback(void *instance, uint8_t commandStationIndex);
#endif // WIFI_ENABLED

private:
  bool _connected;
#ifdef WIFI_ENABLED
  bool _receivedUserSelection;
  uint8_t _selectedCommandStation;
  uint8_t _commandStationCount;
  CommandStationDetails *_commandStationList;
  bool _wifiStarted;
  unsigned long _wifiRetryDelay;
  unsigned long _lastWifiRetry;
  uint8_t _wifiRetries;
  unsigned long _serverRetryDelay;
  unsigned long _lastServerRetry;
  uint8_t _serverRetries;

  WiFiClient _wifiClient;

  /// @brief Ensure WiFi client is connected and reconnects if disconnected
  bool _connectWiFi(unsigned long currentMillis);

  /// @brief Ensure server is connected and reconnects if disconnected
  bool _connectServer(unsigned long currentMillis);
#endif // WIFI_ENABLED
};

#endif // CONNECTIONMANAGER_H
