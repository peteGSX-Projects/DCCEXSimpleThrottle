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

#ifndef APPORCHESTRATOR_H
#define APPORCHESTRATOR_H

#include "DisplayInterface.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"
#include "ScreenInterface.h"

enum class AppState { STARTUP, MENU, OPERATION };

/// @brief This class is for the overall application orchestration to coordinate all the user interactions, screens, and
/// displays
class AppOrchestrator {
public:
  /// @brief Constructor for the application orchestrator object
  /// @param displayInterface Pointer to the display interface to ensure is updated
  /// @param userConfirmationInterface Pointer to the user confirmation interface to monitor
  /// @param userSelectionInterface Pointer the user selection interface to monitor
  AppOrchestrator(DisplayInterface *displayInterface, UserConfirmationInterface *userConfirmationInterface,
                  UserSelectionInterface *userSelectionInterface);

  /// @brief Call this method to start all the associated interfaces
  void begin();

  /// @brief Call this method at least once per main loop iteration to monitor for user interactions and ensure the
  /// display is updated
  void update();

private:
  DisplayInterface *_displayInterface;
  UserConfirmationInterface *_userConfirmationInterface;
  UserSelectionInterface *_userSelectionInterface;
  AppState _currentAppState;

  ScreenInterface *_tempScreen;

  /// @brief When in startup mode, show the startup screen and wait for user interaction
  void _handleStartupState();
  
  /// @brief 
  void _handleMenuState();
  
  /// @brief 
  void _handleOperationState();
};

#endif // APPORCHESTRATOR_H
