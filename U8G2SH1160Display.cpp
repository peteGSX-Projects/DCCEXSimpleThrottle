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
  _throttleFont = THROTTLE_FONT;
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

void U8G2SH1106Display::displayStartupScreen(const char *headerText, const char *version) {
  if (needsRedraw()) {
    setNeedsRedraw(false);
    _displayHeader(headerText);
    _displayStartupInfo(version);
  }
}

void U8G2SH1106Display::displayProgressScreen(const char *activity, uint8_t counter) {
  if (needsRedraw()) {
    setNeedsRedraw(false);
    _clearDisplay();
    _displayHeader(activity);
  }
  _displayProgress(counter);
}

void U8G2SH1106Display::displayErrorScreen(const char *errorText) {
  if (needsRedraw()) {
    setNeedsRedraw(false);
    _clearDisplay();
    _displayErrorMessage(errorText);
  }
}

void U8G2SH1106Display::displayMenuScreen(const char *menuName, BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex,
                                          bool selectionChanged) {
  if (needsRedraw()) {
    setNeedsRedraw(false);
    setNeedsMenuRefresh(false);
    _clearDisplay();
    _displayHeader(menuName);
    _displayMenuFooter();
    uint8_t pageNumber = _displayMenuItems(firstMenuItem, selectedItemIndex);
    _displayPageNumber(pageNumber);
  } else if (selectionChanged || needsMenuRefresh()) {
    setNeedsMenuRefresh(false);
    uint8_t pageNumber = _displayMenuItems(firstMenuItem, selectedItemIndex);
    _displayPageNumber(pageNumber);
  }
}

void U8G2SH1106Display::displayThrottleScreen(const char *locoName, uint8_t speed, Direction direction,
                                              TrackPower trackPower, bool speedChanged, bool directionChange,
                                              bool trackPowerChanged) {
  if (needsRedraw()) {
    setNeedsRedraw(false);
    _clearDisplay();
    _displayLocoSpeed(speed);
    _displayLocoDirection(direction);
    _displayLocoName(locoName);
    _displayTrackPowerState(trackPower);
    return;
  }
  if (speedChanged) {
    _displayLocoSpeed(speed);
  }
  if (directionChange) {
    _displayLocoDirection(direction);
  }
  if (trackPowerChanged) {
    _displayTrackPowerState(trackPower);
  }
}

uint8_t U8G2SH1106Display::_calculateMenuItemsPerPage() {
  _oled->setFont(_menuFont);
  uint8_t fontHeight = _oled->getMaxCharHeight();
  uint8_t itemsPerPage = _calculateMenuItemHeight() / fontHeight;
  return itemsPerPage;
}

uint16_t U8G2SH1106Display::_calculateHeaderHeight() {
  _oled->setFont(_menuFont);
  uint16_t fontHeight = _oled->getMaxCharHeight();
  return fontHeight + 1;
}

uint16_t U8G2SH1106Display::_calculateMenuItemHeight() {
  uint16_t menuItemHeight = _oled->getHeight() - _calculateHeaderHeight() - _calculateMenuFooterHeight();
  return menuItemHeight;
}

uint16_t U8G2SH1106Display::_calculateMenuFooterHeight() {
  _oled->setFont(_menuFont);
  uint16_t fontHeight = _oled->getMaxCharHeight();
  return fontHeight + 2;
}

void U8G2SH1106Display::_clearDisplay() {
  _oled->clear();
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayHeader(const char *headerText) {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  uint16_t x = 0;
  uint16_t y = _calculateHeaderHeight();
  uint16_t lineWidth = _oled->getWidth();
  _oled->drawHLine(x, y, lineWidth);
  _oled->drawStr(x, y - 1, headerText);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayStartupInfo(const char *version) {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  uint16_t fontHeight = _oled->getMaxCharHeight();
  uint16_t x = 0;
  uint16_t y = _calculateHeaderHeight() + fontHeight + 1;
  const char *text = "Version: ";
  uint16_t textWidth = _oled->getStrWidth(text);
  _oled->drawStr(x, y, text);
  x += textWidth;
  _oled->drawStr(x, y, version);
  y = _oled->getHeight() - 1;
  x = 0;
  _oled->drawStr(x, y, "Press button to continue");
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
  uint16_t y = _calculateHeaderHeight() + 1;
  _oled->setDrawColor(0);
  _oled->drawBox(x, y, _oled->getWidth(), (fontHeight * getMenuItemsPerPage()) + 1);
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
      const char *displayName = displayItem->getName();
      if (displayName == nullptr) {
        displayName = "No display name";
      }
      _oled->drawStr(x, y += fontHeight, displayName);
    }
  }
  _oled->sendBuffer();
  return currentPage + 1;
}

void U8G2SH1106Display::_displayMenuFooter() {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  const char *text = "Page # ";
  const char *page = "99";
  uint16_t textWidth = _oled->getStrWidth(text);
  uint16_t pageWidth = _oled->getStrWidth(page);
  uint16_t displayWidth = _oled->getWidth();
  uint16_t x = displayWidth - pageWidth - textWidth - 1;
  uint16_t lineWidth = _oled->getWidth();
  uint16_t footerHeight = _calculateMenuFooterHeight();
  uint16_t y = _oled->getHeight() - footerHeight;
  _oled->drawHLine(0, y, lineWidth);
  y = _oled->getHeight() - 1;
  _oled->drawStr(x, y, text);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayPageNumber(uint8_t pageNumber) {
  _oled->setFont(_menuFont);
  char pageBuffer[4];
  snprintf(pageBuffer, sizeof(pageBuffer), "%d", pageNumber);
  const char *page = "99";
  uint16_t pageWidth = _oled->getStrWidth(page);
  uint16_t displayWidth = _oled->getWidth();
  uint16_t x = displayWidth - pageWidth - 1;
  uint16_t fontHeight = _oled->getMaxCharHeight();
  uint16_t y = _oled->getHeight() - 1;
  _oled->setDrawColor(0);
  _oled->drawBox(x, y - fontHeight, pageWidth, fontHeight);
  _oled->setDrawColor(1);
  _oled->drawStr(x, y, pageBuffer);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayProgress(uint8_t counter) {
  _oled->setFont(_defaultFont);
  uint16_t indicatorWidth = _oled->getMaxCharWidth();
  uint16_t indicatorHeight = _oled->getMaxCharHeight();
  uint16_t x = 0;
  uint16_t y = _calculateHeaderHeight() + (indicatorHeight * 3);
  for (uint8_t i = 0; i < counter; i++) {
    _oled->drawStr(x, y, ".");
    x += indicatorWidth;
  }
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayErrorMessage(const char *errorMessage) {
  _oled->setFont(_defaultFont);
  uint16_t x = 0;
  uint16_t y = 10;
  _oled->drawStr(x, y, errorMessage);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayLocoSpeed(uint8_t speed) {
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

void U8G2SH1106Display::_displayLocoDirection(Direction direction) {
  const char *directionText;
  if (direction == Direction::Reverse) {
    directionText = "Reverse";
  } else {
    directionText = "Forward";
  }
  _oled->setFont(_throttleFont);
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

void U8G2SH1106Display::_displayLocoName(const char *name) {
  _oled->setCursor(0, 50);
  _oled->setFont(_throttleFont);
  _oled->print(F("                      "));
  _oled->setCursor(0, 50);
  _oled->print(name);
  _oled->sendBuffer();
}

void U8G2SH1106Display::_displayTrackPowerState(TrackPower trackPower) {
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
