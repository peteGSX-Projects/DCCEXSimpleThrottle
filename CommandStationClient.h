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

#ifndef COMMANDSTATIONCLIENT_H
#define COMMANDSTATIONCLIENT_H

#include "CommandStationListener.h"
#include "Defines.h"
#include <DCCEXProtocol.h>

/// @brief
class CommandStationClient {
public:
  /// @brief Constructor for the CommandStation client
  /// @param consoleStream Pointer to the stream for logging
  /// @param commandStationLister Pointer to the listener to respond to broadcasts/responses
  CommandStationClient(Stream *logStream, CommandStationListener *commandStationLister);

  /// @brief Setup the CommandStation client with log stream and listener ready to connect
  void begin();

  /// @brief Set the stream object used to connect to the CommandStation, call after begin()
  /// Once set, the client is flagged as connected which will initiate communication with the CommandStation
  /// @param connectionStream Pointer to the stream object (WiFi client or serial)
  void setConnectionStream(Stream *connectionStream);

  /// @brief Ensure client is updated regularly
  void update();

  /// @brief Check if the CommandStation client is connected
  /// @return True|False
  bool isConnected();

  /// @brief Get the actual DCCEXProtocol client to interact with
  /// @return Pointer to the DCCEXProtocol client
  DCCEXProtocol *getClient();

private:
  Stream *_logStream;
  CommandStationListener *_commandStationListener;
  Stream *_connectionStream;
  DCCEXProtocol *_commandStationClient;
  bool _isConnected;
  uint8_t _rosterMaxRetries;
  uint8_t _rosterRetry;
  unsigned long _lastRosterRetry;
  unsigned long _rosterRetryDelay;
};

#endif // COMMANDSTATIONCLIENT_H
