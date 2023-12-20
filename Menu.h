/*
 *  © 2023 Peter Cole
 *
 *  This file is for a serially connected throttle for a DCC-EX EX-CommandStation.
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

class MenuItem {
public:
  /// @brief Constructor
  /// @param label Text label to display in the menu
  MenuItem(const char* label);

  /// @brief Get menu item label
  /// @return 
  const char* getLabel();

  /// @brief Set the next MenuItem
  /// @param item 
  void setNext(MenuItem* item);
  
  /// @brief Get the next MenuItem
  /// @return 
  MenuItem* getNext();

  /// @brief Set the index of this item
  /// @param index 
  void setIndex(int index);

  /// @brief Get the index of this item
  /// @return 
  int getIndex();

private:
  const char* _label;
  int _index;
  MenuItem* _next;

};

class LocoMenuItem : public MenuItem {
public:
  /// @brief Constructor, provide the Loco object
  /// @param object 
  LocoMenuItem(Loco* object);

  /// @brief Get the Loco object
  /// @return 
  Loco* getLocoObject();

private:
  Loco* _locoObject;

};

class Menu {
public:
  Menu(const char* label);

  void addItem(MenuItem* item);

  MenuItem* getFirst();

  MenuItem* getItemAtIndex(int index);

  int getItemCount();

  int getItemsPerPage();

  int getCurrentPage();

  void setCurrentPage(int page);

  const char* getLabel();

private:
  const char* _label;
  MenuItem* _first;
  int _itemCount;
  int _itemsPerPage=5;
  int _currentPage;
  int _currentIndex;

};

#endif
