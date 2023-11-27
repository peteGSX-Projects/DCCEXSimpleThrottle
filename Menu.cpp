#include <Arduino.h>
#include "Menu.h"

MenuItem::MenuItem(char* name, Loco* object) {
  _locoName=name;
  _locoObject=object;
  _index=_nextIndex++;
}

void MenuItem::setNext(MenuItem* item) {
  _next=item;
}

MenuItem* MenuItem::getNext() {
  return _next;
}

int MenuItem::getIndex() {
  return _index;
}

char* MenuItem::getLocoName() {
  return _locoName;
}

Loco* MenuItem::getLocoObject() {
  return _locoObject;
}

Menu::Menu() {
  _firstItem=nullptr;
  _itemCount=0;
  _currentPage=0;
};

void Menu::addItem(MenuItem* item) {
  if (this->_firstItem==nullptr) {
    this->_firstItem=item;
  } else {
    MenuItem* current=this->_firstItem;
    while (current->getNext()!=nullptr) {
      current=current->getNext();
    }
    current->setNext(item);
  }
  _itemCount++;
}

MenuItem* Menu::getFirst() {
  return _firstItem;
}

MenuItem* Menu::getItemAtIndex(int index) {
  for (MenuItem* item=_firstItem; item; item=item->getNext()) {
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
