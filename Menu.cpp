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

#include <Arduino.h>
#include "Menu.h"

LocoMenuItem::LocoMenuItem(char* name, Loco* object) {
  _locoName=strdup(name);
  _locoObject=object;
  _nextLoco=nullptr;
}

void LocoMenuItem::setNextLoco(LocoMenuItem* item) {
  _nextLoco=item;
}

LocoMenuItem* LocoMenuItem::getNextLoco() {
  return _nextLoco;
}

void LocoMenuItem::setIndex(int index) {
  _index=index;
}

int LocoMenuItem::getIndex() {
  return _index;
}

const char* LocoMenuItem::getLocoName() {
  return _locoName;
}

Loco* LocoMenuItem::getLocoObject() {
  return _locoObject;
}

Menu::Menu() {
  _firstLoco=nullptr;
  _itemCount=0;
  _currentPage=0;
  _currentIndex=0;
};

void Menu::addLocoItem(LocoMenuItem* item) {
  if (this->_firstLoco==nullptr) {
    this->_firstLoco=item;
  } else {
    LocoMenuItem* current=this->_firstLoco;
    while (current->getNextLoco()!=nullptr) {
      current=current->getNextLoco();
    }
    current->setNextLoco(item);
  }
  item->setIndex(_currentIndex++);
  _itemCount++;
}

LocoMenuItem* Menu::getFirstLoco() {
  return _firstLoco;
}

LocoMenuItem* Menu::getItemAtIndex(int index) {
  for (LocoMenuItem* item=_firstLoco; item; item=item->getNextLoco()) {
    if (item->getIndex()==index) {
      return item;
    }
  }
  return nullptr;
}

int Menu::getItemCount() {
  return _itemCount;
}

int Menu::getItemsPerPage() {
  return _itemsPerPage;
}

int Menu::getCurrentPage() {
  return _currentPage;
}

void Menu::setCurrentPage(int page) {
  _currentPage=page;
}
