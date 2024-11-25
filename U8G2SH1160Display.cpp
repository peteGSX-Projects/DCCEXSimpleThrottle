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

#include "U8G2SH1106Display.h"

U8G2SH1106Display::U8G2SH1106Display() {
#if (OLED_CONNECTION == OLED_I2C)
  _oled = new OLED_TYPE(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);
#elif (OLED_CONNECTION == OLED_SPI)
#include <SPI.h>
  _oled = new OLED_TYPE(U8G2_R0, CS_PIN, DC_PIN);
#endif // OLED_CONNECTION
  _defaultFont = DEFAULT_FONT;
  _menuFont = MENU_FONT;
  _speedFont = SPEED_FONT;
  _directionFont = DIRECTION_FONT;
  _addressFont = ADDRESS_FONT;
  _eStopFont = ESTOP_FONT;
  _wifiFont = WIFI_FONT;
  _csFont = CS_FONT;
  _errorFont = ERROR_FONT;
  // setMenuItemsPerPage(5);
  setMenuItemsPerPage(_calculateMenuItemsPerPage());
  setNeedsRedraw(true);
}

void U8G2SH1106Display::begin() {
  _oled->begin();
  _oled->setFont(_defaultFont);
  _oled->clear();
  _oled->sendBuffer();
}

void U8G2SH1106Display::clear() {
  _oled->clear();
  _oled->sendBuffer();
}

void U8G2SH1106Display::displayHeader(const char *headerText) {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  _oled->drawHLine(0, 7, 128);
  _oled->setCursor(0, 6);
  _oled->print(headerText);
  _oled->sendBuffer();
}

void U8G2SH1106Display::displayMenuItems(BaseMenuItem *firstItem, uint8_t selectedIndex) {
  if (!firstItem)
    return;
  uint8_t itemsPerPage = getMenuItemsPerPage();
  uint8_t currentPage = (selectedIndex / itemsPerPage);
  uint8_t startIndex = currentPage * itemsPerPage;
  _oled->setFont(_menuFont);
  uint8_t fontHeight = _oled->getMaxCharHeight();
  uint16_t x = 0;
  uint16_t y = 11;
  for (uint8_t i = 0; i < itemsPerPage; i++) {
    uint8_t index = startIndex + i;
    BaseMenuItem *displayItem = nullptr;
    for (BaseMenuItem *item = firstItem; item; item = item->getNext()) {
      if (item->getIndex() == index) {
        displayItem = item;
        break;
      }
    }
    if (displayItem) {
      _oled->setDrawColor(1);
      if (index == selectedIndex) {
        _oled->setDrawColor(0); // Highlight if this item is selected
      }
      _oled->drawStr(x, y += fontHeight, displayItem->getName());
    }
  }
  displayPageNumber(currentPage + 1, false);
  _oled->sendBuffer();
}

void U8G2SH1106Display::displayPageNumber(uint8_t pageNumber, bool pageChanged) {
  _oled->setDrawColor(1);
  _oled->drawHLine(0, 55, 128);
  _oled->setCursor(80, 63);
  _oled->print(F("Page # "));
  _oled->setCursor(115, 63);
  _oled->print("   ");
  _oled->setCursor(115, 63);
  _oled->print(pageNumber);
  _oled->sendBuffer();
}

void U8G2SH1106Display::displayMenu(const char *menuName, BaseMenuItem *menuItems, uint8_t selectedItemIndex,
                                    bool selectionChanged) {
  if (needsRedraw()) {
    CONSOLE.print("Menu items per page: ");
    CONSOLE.println(getMenuItemsPerPage());
    setNeedsRedraw(false);
    _clearDisplay();
    _displayHeader(menuName);
    _displayMenuFooter();
    uint8_t pageNumber = _displayMenuItems(menuItems, selectedItemIndex);
    _displayPageNumber(pageNumber);
  } else if (selectionChanged) {
    uint8_t pageNumber = _displayMenuItems(menuItems, selectedItemIndex);
    _displayPageNumber(pageNumber);
  }
  /*
  If needsRedraw:
  - displayHeader()
  - displayMenuItems()
  - displayPageNumber()
  If selectionChanged:
  - displayMenuItems() - but only change highlight
  If pageChanged:
  - displayPageNumber() - but only change page number
  - Page number only known to the display, and only display can flag if it changed
  - Need to clear all menu items when changing page
  */
}

void U8G2SH1106Display::displaySoftwareVersion(const char *version) {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  uint8_t fontHeight = _oled->getMaxCharHeight();
  _oled->setCursor(0, 19);
  _oled->print("Version: ");
  _oled->print(version);
  _oled->setCursor(0, 19 + (fontHeight * 4));
  _oled->print("Press button to continue");
  _oled->sendBuffer();
}

void U8G2SH1106Display::updateSpeed(uint8_t speed) {
  _oled->setFont(_speedFont);
  uint16_t displayWidth = _oled->getWidth();
  uint8_t fontHeight = _oled->getMaxCharHeight();
  char speedBuffer[4];
  snprintf(speedBuffer, sizeof(speedBuffer), "%d", speed);
  uint16_t speedWidth = _oled->getStrWidth(speedBuffer);
  uint16_t clearWidth = _oled->getStrWidth("999");
  uint16_t clearX = (displayWidth - clearWidth) / 2;
  uint16_t x = (displayWidth - speedWidth) / 2;
  uint16_t y = 20;
  _oled->setDrawColor(0);
  _oled->drawBox(clearX, y - fontHeight, clearWidth, fontHeight);
  _oled->setDrawColor(1);
  _oled->setCursor(x, y);
  _oled->print(speed);
  _oled->sendBuffer();
}

void U8G2SH1106Display::updateLocoName(const char *name) {
  _oled->setCursor(0, 50);
  _oled->setFont(_addressFont);
  _oled->print(F("                      "));
  _oled->setCursor(0, 50);
  _oled->print(name);
  _oled->sendBuffer();
}

void U8G2SH1106Display::updateLocoDirection(Direction direction) {
  const char *directionText;
  if (direction == Direction::Reverse) {
    directionText = "Reverse";
  } else {
    directionText = "Forward";
  }
  _oled->setFont(_directionFont);
  uint16_t displayWidth = _oled->getWidth();
  uint8_t fontHeight = _oled->getMaxCharHeight();
  uint16_t clearWidth = _oled->getStrWidth(directionText);
  uint16_t x = (displayWidth - clearWidth) / 2;
  uint16_t y = 35;
  _oled->setDrawColor(0);
  _oled->drawBox(x, y - fontHeight, clearWidth, fontHeight);
  _oled->setDrawColor(1);
  _oled->setCursor(x, y);
  _oled->print(directionText);
  _oled->sendBuffer();
}

void U8G2SH1106Display::updateTrackPowerState(TrackPower trackPower) {
  _oled->drawHLine(0, 55, 128);
  _oled->setCursor(50, 63);
  _oled->setFont(_menuFont);
  _oled->print(F("Track power: "));
  _oled->setCursor(112, 63);
  _oled->print("   ");
  _oled->setCursor(112, 63);
  switch (trackPower) {
  case TrackPower::PowerOff:
    _oled->print(F("Off"));
    break;

  case TrackPower::PowerOn:
    _oled->print(F("On"));
    break;

  case TrackPower::PowerUnknown:
    _oled->print(F("?"));
    break;

  default:
    break;
  }
  _oled->sendBuffer();
}

void U8G2SH1106Display::_clearDisplay() {
  _oled->clear();
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayHeader(const char *headerText) {
  _calculateHeaderHeight();
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  uint16_t x = 0;
  uint16_t fontHeight = _oled->getMaxCharHeight();
  uint16_t lineWidth = _oled->getWidth();
  // _oled->drawHLine(0, 7, 128);
  // _oled->setCursor(0, 6);
  _oled->drawHLine(x, fontHeight + 1, lineWidth);
  _oled->setCursor(x, fontHeight);
  _oled->print(headerText);
  _oled->sendBuffer();
}

uint8_t U8G2SH1106Display::_displayMenuItems(BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex) {
  if (!firstMenuItem)
    return 0;
  uint8_t itemsPerPage = getMenuItemsPerPage();
  uint8_t currentPage = (selectedItemIndex / itemsPerPage);
  uint8_t startIndex = currentPage * itemsPerPage;
  _oled->setFont(_menuFont);
  uint8_t fontHeight = _oled->getMaxCharHeight();
  uint16_t x = 0;
  uint16_t y = 11;
  for (uint8_t i = 0; i < itemsPerPage; i++) {
    uint8_t index = startIndex + i;
    BaseMenuItem *displayItem = nullptr;
    for (BaseMenuItem *item = firstMenuItem; item; item = item->getNext()) {
      if (item->getIndex() == index) {
        displayItem = item;
        break;
      }
    }
    if (displayItem) {
      _oled->setDrawColor(1);
      if (index == selectedItemIndex) {
        _oled->setDrawColor(0); // Highlight if this item is selected
      }
      _oled->drawStr(x, y += fontHeight, displayItem->getName());
    }
  }
  _oled->sendBuffer();
  return currentPage + 1;
}

void U8G2SH1106Display::_displayPageNumber(uint8_t pageNumber) {
  _oled->setDrawColor(1);
  _oled->setCursor(115, 63);
  _oled->print("   ");
  _oled->setCursor(115, 63);
  _oled->print(pageNumber);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayMenuFooter() {
  _calculateMenuFooterHeight();
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  uint16_t x = 0;
  uint16_t fontHeight = _oled->getMaxCharHeight();
  uint16_t lineWidth = _oled->getWidth();
  uint16_t y = _oled->getHeight() - fontHeight - 1;
  // _oled->drawHLine(0, 55, 128);
  // _oled->setCursor(80, 63);
  _oled->drawHLine(0, y, lineWidth);
  y += fontHeight;
  _oled->drawStr(x, y, "Page #");
  // _oled->setCursor(x, y);
  // _oled->print("Page # ");
  _oled->sendBuffer();
}

uint8_t U8G2SH1106Display::_calculateMenuItemsPerPage() {
  _oled->setFont(_menuFont);
  uint8_t fontHeight = _oled->getMaxCharHeight();
  uint8_t itemsPerPage = _calculateMenuItemHeight() / fontHeight;
  return itemsPerPage;
}

uint16_t U8G2SH1106Display::_calculateHeaderHeight() {
  /*
  Menu header starts at 6
  Header line is at 7
  Menu items start at 11
  Footer line is at 55
  Footer text is at 63
  */
  _oled->setFont(_menuFont);
  uint16_t fontHeight = _oled->getMaxCharHeight();
  CONSOLE.print("width|height|fontHeight: ");
  CONSOLE.print(_oled->getWidth());
  CONSOLE.print("|");
  CONSOLE.print(_oled->getHeight());
  CONSOLE.print("|");
  CONSOLE.println(fontHeight);
  return 10;
  }

uint16_t U8G2SH1106Display::_calculateMenuItemHeight() {
  uint16_t menuItemHeight = _oled->getHeight() - _calculateHeaderHeight() - _calculateMenuFooterHeight();
  return menuItemHeight;
}

uint16_t U8G2SH1106Display::_calculateMenuFooterHeight() { return 9; }

void U8G2SH1106Display::_clearMenuItems() {}
