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

#ifndef BASEMENUITEM_H
#define BASEMENUITEM_H

#include <Arduino.h>

/// @brief Base class for all menu item types, and all menu item types must inherit from this.
/// Every menu item has a name, which is what appears on screen for the user to select.
/// Every menu item also needs an index to assist with selecting specific items.
/// All menu items form a linked list associated with a menu.
class BaseMenuItem {
public:
  /// @brief Constructor for each MenuItem object
  /// @param name Pointer to the text name char array to display in the menu
  BaseMenuItem(const char *name);

  /// @brief Get menu item name
  /// @return Pointer to the char array containing the item name
  const char *getName();

  /// @brief Set the next menu item
  /// @param item Pointer to the next menu item
  void setNext(BaseMenuItem *item);

  /// @brief Get the next menu item
  /// @return Pointer to the next menu item
  BaseMenuItem *getNext();

  /// @brief Set the index of this menu item
  /// @param index Integer index of this menu item
  void setIndex(uint8_t index);

  /// @brief Get the index of this item
  /// @return Integer index of this menu item
  uint8_t getIndex();

private:
  const char *_name;   // pointer to the char array containing the name
  uint8_t _index;      // index of this menu item
  BaseMenuItem *_next; // pointer to the next menu item
};

#endif // MENU_H
