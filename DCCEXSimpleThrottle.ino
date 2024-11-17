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

#include "Button.h"
#include "Controller.h"
#include "Defines.h"
#include "Menu.h"
#include "MenuScreen.h"
#include "OLEDDisplay.h"
#include "OperatingScreen.h"
#include "Rotary.h"
#include "RotaryEncoder.h"
#include "Version.h"
#include "avdweb_Switch.h"
#include <Arduino.h>
#include <U8g2lib.h>

/// @brief Create the OLED object based on user defined connection type
#if (OLED_CONNECTION == OLED_I2C)
OLED_TYPE oled(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);
#elif (OLED_CONNECTION == OLED_SPI)
#include <SPI.h>
OLED_TYPE oled(U8G2_R0, CS_PIN, DC_PIN);
#endif // OLED_CONNECTION

/// @brief Create the actual physical button object using defaults in Defines.h (or overrides in myConfig.h)
/// @param BUTTON_PIN Pin the button is connected to
/// @param BUTTON_PIN_MODE Default to INPUT_PULLUP, can be INPUT if active high or external pullups available
/// @param BUTTON_PIN_POLARITY Default to LOW, can be HIGH if appropriate
/// @param BUTTON_DEBOUNCE_PERIOD Default 50ms, delay period to avoid button mechanical bounce issues
/// @param BUTTON_LONG_PRESS_PERIOD Default 500ms, delay period to detect a long press vs. a click/double click
/// @param BUTTON_DOUBLE_CLICK_PERIOD Default 250ms, period in which two clicks are detected as a double click
/// @param BUTTON_DEGLITCH_PERIOD Default to 10ms, delay period to avoid button glitches
/// @return Switch object, unused in this context
Switch physicalButton(BUTTON_PIN, BUTTON_PIN_MODE, BUTTON_PIN_POLARITY, BUTTON_DEBOUNCE_PERIOD,
                      BUTTON_LONG_PRESS_PERIOD, BUTTON_DOUBLE_CLICK_PERIOD, BUTTON_DEGLITCH_PERIOD);

/// @brief Create the button object
/// @param button Pointer to the physical switch object
/// @return Button object, unused in this context
Button button(&physicalButton);

/// @brief Create the actual physical rotary encoder object using defaults in Defines.h (or overrides in myConfig.h)
/// @param ENCODER_DT_PIN Pin the encoder's DT pin is connected to
/// @param ENCODER_CLK_PIN Pin the encoder's CLK pin is connected to
/// @return Rotary encoder object, unused in this context
Rotary physicalRotaryEncoder(ENCODER_DT_PIN, ENCODER_CLK_PIN);

/// @brief Create the rotary encoder object
/// @param rotaryEncoder Pointer to the physical rotary encoder object
/// @return RotaryEncoder object, unused in this context
RotaryEncoder rotaryEncoder(&physicalRotaryEncoder);

/// @brief Create the OLED display object
/// @param oled Reference of the existing OLED object
/// @return OLEDDisplay object, unused in this context
OLEDDisplay oledDisplay(&oled);

/// @brief Create the menu to allow selecting an EX-CommandStation and associated WiFi connection
Menu serverMenu("Select server");

/// @brief Create the server menu screen
/// @param
/// @return
MenuScreen serverMenuScreen(&serverMenu);

/// @brief Create the menu to allow selecting a loco from the roster
Menu selectLocoMenu("Select loco");

/// @brief Create the
/// @param
/// @return
MenuScreen selectLocoMenuScreen(&selectLocoMenu);

/// @brief Create the menu to select other actions such as toggling track power etc.
Menu actionMenu("Select action");

/// @brief
/// @param
/// @return
MenuScreen actionMenuScreen(&actionMenu);

/// @brief Create the controller
/// @param button Pointer to the button interacting with this controller
/// @param display Pointer to the display for this controller to manage
/// @param rotaryEncoder Pointer to the rotary encoder interacting with this controller
/// @return Controller object, unused in this context
// Controller controller(&button, &oledDisplay, &rotaryEncoder);

/// @brief Initial setup
void setup() {
  CONSOLE.begin(115200);
  CONSOLE.println("DCC-EX Simple Throttle");
  CONSOLE.print("Version: ");
  CONSOLE.println(VERSION);
  oledDisplay.begin();
  oledDisplay.displayStartupInfo(VERSION);
}

/// @brief Main loop
void loop() {}
