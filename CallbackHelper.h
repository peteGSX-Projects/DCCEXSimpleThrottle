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

#ifndef CALLBACKHELPER_H
#define CALLBACKHELPER_H

#include "ConnectionManager.h"

/// @brief Class to centralise all callbacks for the application
class CallbackHelper {
public:
  /// @brief Wrapper method to enable callbacks to call connection methods
  /// @param instance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  static void staticConnectCallback(void *instance, uint8_t commandStationIndex);
};

#endif // CALLBACKHELPER_H
