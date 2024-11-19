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

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "ScreenInterface.h"

/// @brief Class to manage the various screens in use and switch between them
class ScreenManager {
public:
  /// @brief Constructor for the screen manager object
  ScreenManager();

  /// @brief Add a screen to the linked list of screens
  /// @param screen Pointer to the screen object
  void addScreen(ScreenInterface *screen);

  /// @brief Get the next screen from the linked list
  /// @return Pointer to the screen object
  ScreenInterface *getNext();

  /// @brief Switch to the chosen screen
  /// @param screen Pointer to the screen object
  void switchToScreen(ScreenInterface *screen);

  /// @brief Get the current active screen
  /// @return Pointer to the screen object
  ScreenInterface *getCurrentScreen();

private:
  static ScreenInterface *_first;
  ScreenInterface *_next;
  ScreenInterface *_currentScreen;
};

#endif // SCREENMANGER_H
