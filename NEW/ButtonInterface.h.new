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

#ifndef BUTTONINTERFACE_H
#define BUTTONINTERFACE_H

enum class ButtonEvent { None, SingleClick, DoubleClick, LongPress };

/// @brief Interface class to abstract retrieving physical button events for user interaction
class ButtonInterface {
public:
  /// @brief Start this interface
  virtual void begin() = 0;

  /// @brief Get the current button event
  /// @return ButtonEvent enum
  virtual ButtonEvent getEvent() = 0;

  /// @brief Destructor for this ButtonInterface object
  virtual ~ButtonInterface() = default;
};

#endif // BUTTONINTERFACE_H
