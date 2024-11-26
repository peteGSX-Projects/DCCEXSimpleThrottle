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

#include "ConnectionManager.h"
#include "DisplayInterface.h"
#include "ErrorScreen.h"
#include "MenuManager.h"
#include "OperateScreen.h"
#include "ProgressScreen.h"
#include "StartupScreen.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"

enum class AppState { Startup, SelectServer, ConnectServer, SelectLoco, Operate, SelectAction, Error };

/// @brief This class is for the overall application orchestration to coordinate all the user interactions, screens, and
/// displays
class AppOrchestrator {
public:
  /// @brief Constructor for the application orchestrator object
  /// @param displayInterface Pointer to the display interface to ensure is updated
  /// @param connectionManager Pointer to the connection manager
  /// @param menuManager Pointer to the menu manager
  /// @param userConfirmationInterface Pointer to the user confirmation interface to monitor
  /// @param userSelectionInterface Pointer the user selection interface to monitor
  AppOrchestrator(DisplayInterface *displayInterface, ConnectionManager *connectionManager, MenuManager *menuManager,
                  UserConfirmationInterface *userConfirmationInterface, UserSelectionInterface *userSelectionInterface);

  /// @brief
  void begin();

  /// @brief Call this method at least once per main loop iteration to monitor for user interactions and ensure the
  /// display is updated
  void update();

private:
  DisplayInterface *_displayInterface;
  ConnectionManager *_connectionManager;
  MenuManager *_menuManager;
  UserConfirmationInterface *_userConfirmationInterface;
  UserSelectionInterface *_userSelectionInterface;
  AppState _currentAppState;

  StartupScreen *_startupScreen;
  OperateScreen *_operateScreen;
  ErrorScreen *_errorScreen;
  ProgressScreen *_progressScreen;

  /// @brief Show the startup screen and wait for user interaction before continuing
  void _handleStartupState();

  /// @brief Display the server menu and process user interaction to select one
  void _handleSelectServerState();

  /// @brief Show the connection progress screen until a connection is made
  void _handleConnectServerState();

  /// @brief Show the loco selection menu and process user interaction to select one
  void _handleSelectLocoState();

  /// @brief Show the operate screen and process user interaction
  void _handleOperateState();

  /// @brief Show the select action menu and process user interaction to select one
  void _handleSelectActionState();

  /// @brief Show any errors on screen and process user interaction to recover
  void _handleErrorState();

  /// @brief Switch application states
  /// @param appState State to switch to
  void _switchState(AppState appState);

  /// @brief Display a menu
  /// @param menu Pointer to the menu to be displayed
  void _displayMenu(BaseMenu *menu);
};

#endif // APPORCHESTRATOR_H
