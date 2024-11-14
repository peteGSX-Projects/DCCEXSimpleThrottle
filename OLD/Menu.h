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

#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Base class for each menu item type
class MenuItem {
public:
  /// @brief Constructor for each MenuItem object
  /// @param label Pointer to the text label char array to display in the menu
  MenuItem(const char *label);

  /// @brief Get menu item label
  /// @return Pointer to the char array containing the item label
  const char *getLabel();

  /// @brief Set the next MenuItem object
  /// @param item Pointer to the next MenuItem object
  void setNext(MenuItem *item);

  /// @brief Get the next MenuItem object
  /// @return Pointer to the next MenuItem object
  MenuItem *getNext();

  /// @brief Set the index of this item
  /// @param index Integer index of this MenuItem object
  void setIndex(int index);

  /// @brief Get the index of this item
  /// @return Integer index of this MenuItem object
  int getIndex();

private:
  const char *_label; // pointer to the char array containing the label
  int _index;         // index of the MenuItem
  MenuItem *_next;    // pointer to the next MenuItem object
};

/// @brief Extension of the MenuItem class to cater for loco objects
class LocoMenuItem : public MenuItem {
public:
  /// @brief Constructor for the loco menu item objects
  /// @param object Pointer to the Loco object to associate with this menu item
  LocoMenuItem(Loco *object);

  /// @brief Get the Loco object associated with this menu item
  /// @return Pointer to the Loco object
  Loco *getLocoObject();

private:
  Loco *_locoObject;
};

/// @brief Extension of the MenuItem class to cater for items with associated actions
class ActionMenuItem : public MenuItem {
public:
  typedef void (*Action)();

  /// @brief Constructor for the action menu item objects
  /// @param label Char array to display
  /// @param action Function to call when selected
  ActionMenuItem(const char *label, Action action);

  /// @brief Call the action associated with this menu item object
  void callAction();

private:
  Action _action;
};

/// @brief Class to define each menu object
class Menu {
public:
  /// @brief Constructor for a new Menu object
  /// @param label Char array for the title of the menu to display
  Menu(const char *label);

  /// @brief Add a MenuItem object to this menu
  /// @param item A valid menu item inheriting the MenuItem base class
  void addItem(MenuItem *item);

  /// @brief Get the first MenuItem object associated with this menu
  /// @return Pointer to the MenuItem object
  MenuItem *getFirst();

  /// @brief Get the MenuItem object at the specified index
  /// @param index Index of the item to get
  /// @return Pointer to the MenuItem object
  MenuItem *getItemAtIndex(int index);

  /// @brief Get the number of items in this menu
  /// @return Item count
  int getItemCount();

  /// @brief Get the number of items to display on a page
  /// @return Number of items to display
  int getItemsPerPage();

  /// @brief Get the current page of this menu
  /// @return Current page number
  int getCurrentPage();

  /// @brief Set the current page to display
  /// @param page Current page number
  void setCurrentPage(int page);

  /// @brief Get the menu label
  /// @return Char array
  const char *getLabel();

private:
  const char *_label;
  MenuItem *_first;
  int _itemCount;
  int _itemsPerPage = 5;
  int _currentPage;
  int _currentIndex;
};

#endif
