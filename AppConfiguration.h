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

#include "AppOrchestrator.h"
#include "Button.h"
#include "MenuManager.h"
#include "RotaryEncoder.h"
#include "U8G2SH1106Display.h"

/// @brief Class to perform all application configuration on startup
/// All interfaces and menus are created within this class
class AppConfiguration {
public:
  /// @brief Constructor for the app configuration object
  AppConfiguration();

  /// @brief Start all associated user interfaces and instantiate all objects
  void initialise();

  /// @brief Get the user confirmation interface associated with the config
  /// @return Pointer to the user confirmation interface
  UserConfirmationInterface *getUserConfirmationInterface();

  /// @brief Get the user selection interface associated with the config
  /// @return Pointer to the user selection interface
  UserSelectionInterface *getUserSelectionInterface();

  /// @brief Get the display interface associated with the config
  /// @return Pointer to the display interface
  DisplayInterface *getDisplayInterface();

  /// @brief Get the application orchestrator associated with the config
  /// @return Pointer to the application orchestrator
  AppOrchestrator *getAppOrchestrator();

  /// @brief
  /// @return
  MenuManager *getMenuManager();

private:
  UserConfirmationInterface *_userConfirmationInterface;
  UserSelectionInterface *_userSelectionInterface;
  DisplayInterface *_displayInterface;
  MenuManager *_menuManager;
  AppOrchestrator *_appOrchestrator;
};

#endif // APPCONFIGURATION_H
