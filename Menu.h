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
  MenuItem(char* label);

  const char* getLabel();

  void setNext(MenuItem* item);
  
  MenuItem* getNext();

  void setIndex(int index);

  int getIndex();

private:
  const char* _label;
  int _index;
  MenuItem* _next;

};

class LocoMenuItem : public MenuItem {
public:
  // LocoMenuItem(char* name, Loco* object);
  LocoMenuItem(Loco* object);

  // void setNextLoco(LocoMenuItem* item);

  // void setIndex(int index);
  
  // LocoMenuItem* getNextLoco();

  // int getIndex();

  // const char* getLocoName();

  Loco* getLocoObject();

private:
  // const char* _locoName;
  Loco* _locoObject;
  // int _index;
  // LocoMenuItem* _nextLoco;

};

class Menu {
public:
  Menu();

  void addItem(MenuItem* item);

  MenuItem* getFirst();

  MenuItem* getItemAtIndex(int index);

  int getItemCount();

  int getItemsPerPage();

  int getCurrentPage();

  void setCurrentPage(int page);

private:
  // LocoMenuItem* _firstLoco;
  MenuItem* _first;
  int _itemCount;
  int _itemsPerPage=5;
  int _currentPage;
  int _currentIndex;

};

#endif
