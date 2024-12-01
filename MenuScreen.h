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

#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "BaseMenu.h"
#include "ScreenInterface.h"

class MenuScreen : public ScreenInterface {
public:
  /// @brief
  /// @param menu
  MenuScreen(BaseMenu *menu);

  /// @brief Implement this method to define what to do when user confirmation actions are performed
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

  /// @brief Implement this method to define what to do when user selection actions are performed
  /// @param action UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  void handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) override;

  /// @brief Implement this method to draw the associated screen object on the specified display
  /// @param display Pointer to the display object
  void drawScreen(DisplayInterface *display) override;

private:
  BaseMenu *_menu;
};

#endif // MENUSCREEN_H
