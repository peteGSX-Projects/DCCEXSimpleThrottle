#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

class MenuItem {
public:
  MenuItem(char* name, Loco* object);

  void setNext(MenuItem* item);

  MenuItem* getNext();

  int getIndex();

  char* getLocoName();

  Loco* getLocoObject();

private:
  char* _locoName;
  Loco* _locoObject;
  int _index;
  MenuItem* _next;
  int _nextIndex=0;

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

private:
  MenuItem* _firstItem;
  int _itemCount;
  int _itemsPerPage=5;
  int _currentPage;

};

#endif
