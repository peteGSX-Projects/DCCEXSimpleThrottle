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

U8G2SH1106Display::U8G2SH1106Display(U8G2 *oled) : _oled(oled) {
  _defaultFont = DEFAULT_FONT;
  _menuFont = MENU_FONT;
  _speedFont = SPEED_FONT;
  _directionFont = DIRECTION_FONT;
  _addressFont = ADDRESS_FONT;
  _eStopFont = ESTOP_FONT;
  _wifiFont = WIFI_FONT;
  _csFont = CS_FONT;
  _errorFont = ERROR_FONT;
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

void U8G2SH1106Display::displayStartupInfo(const char *version) {
  _oled->clear();
  _oled->setFont(_defaultFont);
  _oled->setCursor(0, 10);
  _oled->print("DCC-EX Simple Throttle");
  _oled->setCursor(0, 20);
  _oled->print("Version: ");
  _oled->print(version);
  _oled->sendBuffer();
}
