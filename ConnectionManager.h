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

/// @brief Class to manage all WiFi and serial connections used to connect to a CommandStation
class ConnectionManager {
public:
  /// @brief Constructor for the ConnectionManager
  ConnectionManager();

  /// @brief Ensure all connections are alive and retries are managed
  void update();

  /// @brief Check if connections are active
  /// @return True|False
  bool connected();

  /// @brief Get the connection stream managed by this ConnectionManager
  /// @return Pointer to the connection stream object
  Stream *getConnectionStream();

#ifdef WIFI_ENABLED
  /// @brief Check if user has selected a server
  /// @return True|False
  bool receivedUserSelection();

  /// @brief Check if a connection is in progress
  /// @return True|False
  bool isConnecting();

  /// @brief Get the current connection name in progress
  /// @return Connection name
  const char *getConnectionName();

  /// @brief Check if a connection has errored
  /// @return True|False
  bool connectionError();

  /// @brief Get the connection error message
  /// @return Error message
  const char *getConnectionErrorMessage();

  /// @brief Get the current count of retries
  /// @return Retry counter
  uint8_t getRetryCounter();

  /// @brief Flag if this is a new connection attempt to ensure display can be redrawn
  /// @return True|False
  bool newAttempt();

  /// @brief Set the list of CommandStations
  /// @param commandStationList Pointer to the array of CommandStations
  /// @param commandStationCount Count of CommandStations
  void setCommandStationList(CommandStationDetails *commandStationList, uint8_t commandStationCount);

  /// @brief Select the CommandStation to connect to
  /// @param commandStationIndex Index of the list of CommandStationDetails to connect to
  void selectCommandStation(uint8_t commandStationIndex);

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
  uint8_t _wifiMaxRetries;
  uint8_t _wifiRetry;
  unsigned long _serverRetryDelay;
  unsigned long _lastServerRetry;
  uint8_t _serverMaxRetries;
  uint8_t _serverRetry;
  bool _isConnecting;
  const char *_connectionName;
  bool _connectionError;
  const char *_connectionErrorMessage;
  uint8_t _retryCounter;
  bool _newAttempt;

  WiFiClient _wifiClient;

  /// @brief Ensure WiFi client is connected and reconnects if disconnected
  bool _connectWiFi(unsigned long currentMillis);

  /// @brief Ensure server is connected and reconnects if disconnected
  bool _connectServer(unsigned long currentMillis);
#endif // WIFI_ENABLED
};

#endif // CONNECTIONMANAGER_H
