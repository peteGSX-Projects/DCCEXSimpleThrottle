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

#ifndef SCREENINTERFACE_H
#define SCREENINTERFACE_H

#include "ButtonInterface.h"
#include "DisplayInterface.h"
#include "RotaryEncoderInterface.h"

/// @brief Class to support screens of different types responding to rotary encoder movements and button events
class ScreenInterface {
public:
  /// @brief Method to implement to check for rotary encoder movements and button events
  virtual void update() = 0;

  /// @brief Method to implement to handle a rotary encoder movement
  /// @param movement None, Clockwise, or CounterClockwise
  virtual void handleRotation(RotaryEncoderMovement movement) = 0;

  /// @brief Method to implement to handle a button event
  /// @param buttonEvent None, SingleClick, DoubleClick, LongPress
  virtual void handleButtonEvent(ButtonEvent buttonEvent) = 0;

  /// @brief Method to implement to draw the current screen on a display
  /// @param display Pointer to the display interface object
  virtual void drawScreen(DisplayInterface *displayInterface) = 0;

  /// @brief Destructor for this ScreenInterface object
  virtual ~ScreenInterface() = default;

  /// @brief Get the next screen in the linked list
  /// @return Pointer to the screen interface object
  ScreenInterface *getNext() { return _next; }

  /// @brief Set the next screen in the linked list
  /// @param screenInterface Pointer to the screen interface object
  void setNext(ScreenInterface *screenInterface) { _next = screenInterface; }

private:
  ScreenInterface *_next;
};

#endif // SCREENINTERFACE_H
