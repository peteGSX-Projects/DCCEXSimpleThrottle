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
#include "RotaryEncoder.h"
#include "U8G2SH1106Display.h"

/// @brief 
class AppConfiguration {
public:
  /// @brief 
  AppConfiguration();

  /// @brief 
  void begin();

  /// @brief 
  void update();

private:
  UserConfirmationInterface *_userConfirmation;
  UserSelectionInterface *_userSelection;
  DisplayInterface *_display;
};

#endif // APPCONFIGURATION_H
