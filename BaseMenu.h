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

#ifndef BASEMENU_H
#define BASEMENU_H

#include "BaseMenuItem.h"
#include "DisplayInterface.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"
#include <Arduino.h>

/// @brief Class for maintaining a linked list of menu items to form a menu
class BaseMenu {
public:
  /// @brief Constructor for each menu
  /// @param name Pointer to the char array containing the name of the menu
  BaseMenu(const char *name);

  /// @brief Implement this method to display the menu on screen
  /// @param displayInterface Pointer to the physical display
  virtual void displayMenu(DisplayInterface *displayInterface) = 0;

  /// @brief Implement this method to respond to user confirmation actions
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  virtual void handleUserConfirmationAction(UserConfirmationAction action) = 0;

  /// @brief Implement this method to respond to user selection actions
  /// @param action UserSelectionAction::[None|Up|Down]
  virtual void handleUserSelectionAction(UserSelectionAction action) = 0;

  /// @brief Get the name of this menu
  /// @return Pointer to the char array containing the menu name
  const char *getMenuName();

  /// @brief Add a menu item to this menu
  /// @param item Pointer to an existing menu item
  void addItem(BaseMenuItem *menuItem);

  /// @brief Get the first menu item associated with this menu
  /// @return Pointer to the first menu item
  BaseMenuItem *getFirstMenuItem();

  /// @brief Get the menu item at the specified index
  /// @param index Index of the menu item to retrieve
  /// @return Pointer to the specified menu item, or nullptr if it doesn't exist
  BaseMenuItem *getMenuItemAtIndex(uint8_t index);

  /// @brief Get the number of menu items associated with this menu
  /// @return 8 bit integer count of menu items
  uint8_t getMenuItemCount();

private:
  const char *_name;            // Name of this menu
  BaseMenuItem *_firstMenuItem; // Pointer to the first menu item in the linked list
  uint8_t _menuItemCount;       // Count of menu items associated with this menu
  uint8_t _currentItemIndex;    // Incrementing index to ensure each menu item has a unique index
};

#endif // MENU_H
