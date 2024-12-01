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
#include "Defines.h"
#include "DisplayInterface.h"
#include "EventManager.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"
#include <Arduino.h>

/// @brief Class for maintaining a linked list of menu items to form a menu
class BaseMenu {
public:
  /// @brief Implement this method to respond to user confirmation actions
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  virtual void handleUserConfirmationAction(UserConfirmationAction action) = 0;

  /// @brief Method to respond to user selection actions
  /// @param action UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  void handleUserSelectionAction(UserSelectionAction action);

  /// @brief Method to display the menu on screen
  /// @param displayInterface Pointer to the physical display
  void displayMenu(DisplayInterface *displayInterface);

  /// @brief Set the name of this menu
  /// @param name Pointer to the char array containing the name
  void setMenuName(const char *name);

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

  /// @brief Get the index of the currently selected menu item
  /// @return Index of the currently selected menu item
  uint8_t getSelectedItemIndex();

  /// @brief Check if the user selection has changed
  /// @return True|False
  bool getSelectionChanged();

  /// @brief Set the application's event manager instance
  /// @param eventManager Pointer to the event manager instance
  void setEventManager(EventManager *eventManager);

  /// @brief Get the application's event manager instance
  /// @return Pointer to the event manager instance
  EventManager *getEventManager();

private:
  const char *_name = nullptr;            // Name of this menu
  BaseMenuItem *_firstMenuItem = nullptr; // Pointer to the first menu item in the linked list
  uint8_t _menuItemCount = 0;             // Count of menu items associated with this menu
  uint8_t _currentItemIndex = 0;          // Incrementing index to ensure each menu item has a unique index
  uint8_t _selectedItemIndex = 0;         // Index of the item currently selected by the user
  bool _selectionChanged = false;         // Flag if user has selected a different item
  EventManager *_eventManager = nullptr;  // pointer to the application event manager
};

#endif // MENU_H
