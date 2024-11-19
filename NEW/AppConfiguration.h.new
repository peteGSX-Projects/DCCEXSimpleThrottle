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

#ifndef APPCONFIGURATION_H
#define APPCONFIGURATION_H

#include "Button.h"
#include "Controller.h"
#include "Menu.h"
#include "MenuScreen.h"
#include "OperatingScreen.h"
#include "RotaryEncoder.h"
#include "ScreenManager.h"
#include "U8G2SH1106Display.h"

class AppConfiguration {
public:
  /// @brief
  AppConfiguration();

  /// @brief
  /// @param menuList
  /// @param menuCount
  void initialise(Menu **menuList, uint8_t menuCount);

  /// @brief
  /// @return
  Button *getButton();

  /// @brief
  /// @return
  U8G2SH1106Display *getDisplay();

  /// @brief
  /// @return
  RotaryEncoder *getRotaryEncoder();

  /// @brief
  /// @return
  Controller *getController();

  /// @brief
  /// @return
  ScreenManager *getScreenManager();

private:
  Button *_button;
  U8G2SH1106Display *_display;
  RotaryEncoder *_rotaryEncoder;
  ScreenManager *_screenManager;
  Controller *_controller;
  Menu **_menuList;
  uint8_t _menuCount;

  void _setupHardware();
  void _setupScreens();
};

#endif // APPCONFIGURATION_H
