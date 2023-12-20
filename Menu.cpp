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

MenuItem::MenuItem(const char* label)
: _label(strdup(label)) {
  _next=nullptr;
}

const char* MenuItem::getLabel() {
  return _label;
}

void MenuItem::setNext(MenuItem* item) {
  _next=item;
}
  
MenuItem* MenuItem::getNext() {
  return _next;
}

void MenuItem::setIndex(int index) {
  _index=index;
}

int MenuItem::getIndex() {
  return _index;
}

LocoMenuItem::LocoMenuItem(Loco* object)
: MenuItem(object->getName()), _locoObject(object) {}

Loco* LocoMenuItem::getLocoObject() {
  return _locoObject;
}

Menu::Menu(const char* label)
: _label(label) {
  _first=nullptr;
  _itemCount=0;
  _currentPage=0;
  _currentIndex=0;
};

void Menu::addItem(MenuItem* item) {
  if (this->_first==nullptr) {
    this->_first=item;
  } else {
    MenuItem* current=this->_first;
    while (current->getNext()!=nullptr) {
      current=current->getNext();
    }
    current->setNext(item);
  }
  item->setIndex(_currentIndex++);
  _itemCount++;
}

MenuItem* Menu::getFirst() {
  return _first;
}

MenuItem* Menu::getItemAtIndex(int index) {
  for (MenuItem* item=_first; item; item=item->getNext()) {
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

const char* Menu::getLabel() {
  return _label;
}
