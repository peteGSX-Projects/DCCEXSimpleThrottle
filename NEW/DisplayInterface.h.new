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

#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Display interface class to abstract display activities from the display type in use
class DisplayInterface {
public:
  /// @brief Setup display parameters
  virtual void begin() = 0;

  /// @brief Clear the display
  virtual void clear() = 0;

  /// @brief Display the initial startup screen including the software version
  /// @param version Pointer to the char array containing the version
  virtual void displayStartupInfo(const char *version) = 0;

  /// @brief Display the menu header
  /// @param menuName Pointer to the char array containing the menu name
  // virtual void displayMenuHeader(const char *menuName) = 0;

  /// @brief 
  /// @param itemText
  /// @param row
  // virtual void displayMenuItem(const char *itemText, uint8_t row) = 0;

  /// @brief
  /// @param speed
  // virtual void displaySpeed(uint8_t speed);

  /// @brief
  /// @param direction
  // virtual void displayDirection(Direction direction);

  /// @brief
  /// @param address
  // virtual void displayLocoAddress(uint16_t address);

  /// @brief
  /// @param trackPower
  // virtual void displayTrackPower(TrackPower trackPower);

  /// @brief Destructor for this DisplayInterface object
  virtual ~DisplayInterface() = default;
};

#endif // DISPLAYINTERFACE_H
