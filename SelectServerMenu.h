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

#ifndef SELECTSERVERMENU_H
#define SELECTSERVERMENU_H

#include "BaseMenu.h"
#include "ConnectionManager.h"
#include "ServerMenuItem.h"

class SelectServerMenu : public BaseMenu {
public:
  /// @brief Constructor for each menu
  /// @param name Pointer to the char array containing the name of the menu
  SelectServerMenu(const char *name);

  /// @brief Implement this method to respond to user confirmation actions
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

  /// @brief
  /// @param connectionCallback
  /// @param connectionManager
  void setConnectionCallback(void (*connectionCallback)(void *, uint8_t), ConnectionManager *connectionManager);

private:
  void (*_connectionCallback)(void *, uint8_t);
  ConnectionManager *_connectionManager;

  void _initiateServerConnection(BaseMenuItem *item);
};

#endif // SELECTSERVERMENU_H
