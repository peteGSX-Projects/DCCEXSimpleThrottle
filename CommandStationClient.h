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

  /// @brief Ensure client is updated regularly
  void update();

private:
  Stream *_logStream;
  CommandStationListener *_commandStationListener;
  DCCEXProtocol *_commandStationClient;
};

#endif // COMMANDSTATIONCLIENT_H
