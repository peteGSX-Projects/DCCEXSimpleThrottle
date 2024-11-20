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
  setMenuItemsPerPage(5);
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

void U8G2SH1106Display::displayMenuItem(uint8_t index, const char *itemText, bool selected) {}

void U8G2SH1106Display::displaySoftwareVersion(const char *version) {
  _oled->setDrawColor(1);
  _oled->setFont(_menuFont);
  _oled->setCursor(0, 19);
  _oled->print("Version: ");
  _oled->print(version);
  _oled->sendBuffer();
}

void U8G2SH1106Display::updateSpeed(uint8_t speed) {
  _oled->setCursor(40, 20);
  _oled->setFont(_speedFont);
  _oled->print(F("   "));
  _oled->setCursor(40, 20);
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
  _oled->setCursor(30, 35);
  _oled->setFont(_directionFont);
  _oled->print(F("       "));
  _oled->setCursor(30, 35);
  if (direction == Direction::Reverse) {
    _oled->print(F("Reverse"));
  } else {
    _oled->print(F("Forward"));
  }
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
