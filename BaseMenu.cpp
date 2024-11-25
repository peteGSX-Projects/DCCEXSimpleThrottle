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

#include "BaseMenu.h"

void BaseMenu::handleUserSelectionAction(UserSelectionAction action) {
  switch (action) {
  case UserSelectionAction::Up:
    _selectionChanged = true;
    if (_selectedItemIndex > 0) {
      _selectedItemIndex--;
    } else {
      _selectedItemIndex = _menuItemCount - 1;
    }
    break;
  case UserSelectionAction::Down:
    _selectionChanged = true;
    if (_selectedItemIndex < _menuItemCount - 1) {
      _selectedItemIndex++;
    } else {
      _selectedItemIndex = 0;
    }
    break;
  default:
    _selectionChanged = false;
    break;
  }
}

void BaseMenu::displayMenu(DisplayInterface *displayInterface) {
  displayInterface->displayMenuScreen(_name, _firstMenuItem, _selectedItemIndex, _selectionChanged);
}

void BaseMenu::setMenuName(const char *name) { _name = name; }

const char *BaseMenu::getMenuName() { return _name; }

void BaseMenu::addItem(BaseMenuItem *menuItem) {
  if (this->_firstMenuItem == nullptr) { // If it's the first menu item, set it
    this->_firstMenuItem = menuItem;
  } else { // Otherwise add it to the list
    BaseMenuItem *currentMenuItem = this->_firstMenuItem;
    while (currentMenuItem->getNext() != nullptr) {
      currentMenuItem = currentMenuItem->getNext();
    }
    currentMenuItem->setNext(menuItem);
  }
  menuItem->setIndex(_currentItemIndex++); // Set the index and increment
  _menuItemCount++;                        // Increment the item count
}

BaseMenuItem *BaseMenu::getFirstMenuItem() { return _firstMenuItem; }

BaseMenuItem *BaseMenu::getMenuItemAtIndex(uint8_t index) {
  if (!_firstMenuItem) {
    return nullptr;
  }
  BaseMenuItem *menuItem = nullptr;
  for (menuItem = _firstMenuItem; menuItem; menuItem = menuItem->getNext()) {
    if (menuItem->getIndex() == index) {
      return menuItem;
    }
  }
  return nullptr;
}

uint8_t BaseMenu::getMenuItemCount() { return _menuItemCount; }

uint8_t BaseMenu::getSelectedItemIndex() { return _selectedItemIndex; }

bool BaseMenu::getSelectionChanged() { return _selectionChanged; }
