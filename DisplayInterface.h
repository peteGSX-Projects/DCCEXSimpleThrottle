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

/// @brief Interface class to abstract construction of what is displayed on screen from the physical implementations
/// All physical display classes must extend this
/// This allows for different display types and resolutions to be used
class DisplayInterface {
public:
  /// @brief Implement this to perform any initial startup methods or activities
  virtual void begin() = 0;

  /// @brief Implement this to entirely clear a display
  virtual void clear() = 0;

  /// @brief Implement this to display the header text with a horizontal line separator from other items
  /// @param headerText Pointer to the char array containing the header text
  virtual void displayHeader(const char *headerText) = 0;

  /// @brief Implement this to display the menu item's text at the correct position on a display
  /// @param index Index of the item to be displayed
  /// @param itemText Pointer to the char array containing the item's text
  /// @param selected Flag if this item is selected or not so it can be highlighted
  virtual void displayMenuItem(uint8_t index, const char *itemText, bool selected) = 0;

  /// @brief Destructor for the object
  virtual ~DisplayInterface() = default;
};

#endif // DISPLAYINTERFACE_H
