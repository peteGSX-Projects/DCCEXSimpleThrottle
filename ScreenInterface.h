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

#include "DisplayInterface.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"

/// @brief
class ScreenInterface {
public:
  /// @brief Implement this method to define what to do when user confirmation actions are performed
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  virtual void handleUserConfirmationAction(UserConfirmationAction action) = 0;

  /// @brief Implement this method to define what to do when user selection actions are performed
  /// throttleInverted enables an interface to decrease speed when moving up and vice versa, which is handy for a rotary
  /// encoder
  /// @param action UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  /// @param throttleInverted True|False
  virtual void handleUserSelectionAction(UserSelectionAction action, bool throttleInverted = false) = 0;

  /// @brief Implement this method to draw the associated screen object on the specified display
  /// @param display Pointer to the display object
  virtual void drawScreen(DisplayInterface *display) = 0;

  /// @brief Destructor for the object
  virtual ~ScreenInterface() = default;

  /// @brief Get the next screen object in the linked list
  /// @return Pointer to the screen object
  ScreenInterface *getNext() { return _next; }

  /// @brief Set the next screen object in the linked list
  /// @param screen Pointer to a screen object
  void setNext(ScreenInterface *screen) { _next = screen; }

private:
  ScreenInterface *_next;
};

#endif // SCREENINTERFACE_H
