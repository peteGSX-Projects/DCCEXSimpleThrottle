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

#ifndef U8G2SH1106DISPLAY_H
#define U8G2SH1106DISPLAY_H

#include "Defines.h"
#include "DisplayInterface.h"
#include <U8g2lib.h>

class U8G2SH1106Display : public DisplayInterface {
public:
  /// @brief Constructor for the display
  /// @param oled Pointer to the existing I2C or SPI U8G2 OLED object
  U8G2SH1106Display(U8G2 *oled);

  /// @brief Setup display parameters
  void begin() override;

  /// @brief Clear the display
  void clear() override;

  /// @brief Display the initial startup screen including the software version
  /// @param version Pointer to the char array containing the version
  void displayStartupInfo(const char *version) override;

private:
  U8G2 *_oled;
  const uint8_t *_defaultFont;
  const uint8_t *_menuFont;
  const uint8_t *_speedFont;
  const uint8_t *_directionFont;
  const uint8_t *_addressFont;
  const uint8_t *_eStopFont;
  const uint8_t *_wifiFont;
  const uint8_t *_csFont;
  const uint8_t *_errorFont;
};

#endif // U8G2SH1106DISPLAY_H
