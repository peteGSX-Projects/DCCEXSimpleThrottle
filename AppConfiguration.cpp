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

#include "AppConfiguration.h"
#include "Defines.h"
#include "Rotary.h"
#include "avdweb_Switch.h"

AppConfiguration::AppConfiguration() {
  _button = nullptr;
  _display = nullptr;
  _rotaryEncoder = nullptr;
  _screenManager = nullptr;
  _controller = nullptr;
  _menuList = nullptr;
  _menuCount = 0;
}

void AppConfiguration::initialise(Menu **menuList, uint8_t menuCount) {
  if (!menuList)
    return;
  _menuList = menuList;
  _menuCount = menuCount;
  _setupHardware();
  _setupScreens();
  _screenManager = new ScreenManager();
  _controller = new Controller(_button, _display, _rotaryEncoder, _screenManager);
}

Button *AppConfiguration::getButton() { return _button; }

U8G2SH1106Display *AppConfiguration::getDisplay() { return _display; }

RotaryEncoder *AppConfiguration::getRotaryEncoder() { return _rotaryEncoder; }

Controller *AppConfiguration::getController() { return _controller; }

ScreenManager *AppConfiguration::getScreenManager() { return _screenManager; }

void AppConfiguration::_setupHardware() {
/// @brief Create the OLED object based on user defined connection type
#if (OLED_CONNECTION == OLED_I2C)
  OLED_TYPE *sh1106OLED = new OLED_TYPE(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);
#elif (OLED_CONNECTION == OLED_SPI)
#include <SPI.h>
  OLED_TYPE *sh1106OLED = new OLED_TYPE(U8G2_R0, CS_PIN, DC_PIN);
#endif // OLED_CONNECTION

  /// @brief Create the OLED display object
  /// @param oled Reference of the existing OLED object
  _display = new U8G2SH1106Display(sh1106OLED);

  /// @brief Create the actual physical button object using defaults in Defines.h (or overrides in myConfig.h)
  /// @param BUTTON_PIN Pin the button is connected to
  /// @param BUTTON_PIN_MODE Default to INPUT_PULLUP, can be INPUT if active high or external pullups available
  /// @param BUTTON_PIN_POLARITY Default to LOW, can be HIGH if appropriate
  /// @param BUTTON_DEBOUNCE_PERIOD Default 50ms, delay period to avoid button mechanical bounce issues
  /// @param BUTTON_LONG_PRESS_PERIOD Default 500ms, delay period to detect a long press vs. a click/double click
  /// @param BUTTON_DOUBLE_CLICK_PERIOD Default 250ms, period in which two clicks are detected as a double click
  /// @param BUTTON_DEGLITCH_PERIOD Default to 10ms, delay period to avoid button glitches
  Switch *physicalButton = new Switch(BUTTON_PIN, BUTTON_PIN_MODE, BUTTON_PIN_POLARITY, BUTTON_DEBOUNCE_PERIOD,
                                      BUTTON_LONG_PRESS_PERIOD, BUTTON_DOUBLE_CLICK_PERIOD, BUTTON_DEGLITCH_PERIOD);

  /// @brief Create the button object
  /// @param button Pointer to the physical switch object
  _button = new Button(physicalButton);

  /// @brief Create the actual physical rotary encoder object using defaults in Defines.h (or overrides in myConfig.h)
  /// @param ENCODER_DT_PIN Pin the encoder's DT pin is connected to
  /// @param ENCODER_CLK_PIN Pin the encoder's CLK pin is connected to
  Rotary *physicalRotaryEncoder = new Rotary(ENCODER_DT_PIN, ENCODER_CLK_PIN);

  /// @brief Create the rotary encoder object
  /// @param rotaryEncoder Pointer to the physical rotary encoder object
  _rotaryEncoder = new RotaryEncoder(physicalRotaryEncoder);
}

void AppConfiguration::_setupScreens() {
  for (uint8_t i = 0; i < _menuCount; i++) {
    MenuScreen *screen = new MenuScreen(_menuList[i]);
    _screenManager->addScreen(screen);
  }
}
