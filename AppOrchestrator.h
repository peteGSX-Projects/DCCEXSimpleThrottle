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

#include "CommandStationClient.h"
#include "ConnectionManager.h"
#include "DisplayInterface.h"
#include "ErrorScreen.h"
#include "EventListener.h"
#include "MenuManager.h"
#include "ProgressScreen.h"
#include "StartupScreen.h"
#include "ThrottleScreen.h"
#include "UserConfirmationInterface.h"
#include "UserSelectionInterface.h"

enum class AppState { Startup, SelectCommandStation, ConnectCommandStation, SelectLoco, Throttle, SelectAction, Error };

/// @brief This class is for the overall application orchestration to coordinate all the user interactions, screens,
/// displays, connection management, and other application states
class AppOrchestrator : public EventListener {
public:
  /// @brief Constructor for the application orchestrator object
  /// @param displayInterface Pointer to the display interface to ensure is updated
  /// @param connectionManager Pointer to the connection manager
  /// @param menuManager Pointer to the menu manager
  /// @param commandStationClient Pointer to the CommandStation client
  /// @param userConfirmationInterface Pointer to the user confirmation interface to monitor
  /// @param userSelectionInterface Pointer the user selection interface to monitor
  /// @param throttleScreen Pointer to the throttle screen
  AppOrchestrator(DisplayInterface *displayInterface, ConnectionManager *connectionManager, MenuManager *menuManager,
                  CommandStationClient *commandStationClient, UserConfirmationInterface *userConfirmationInterface,
                  UserSelectionInterface *userSelectionInterface, ThrottleScreen *throttleScreen);

  /// @brief Anything required to be initiated when the orchestrator starts is called here
  void begin();

  /// @brief Call this method at least once per main loop iteration to monitor for user interactions, ensure the
  /// display is updated, and connections are managed
  void update();

  /// @brief Implementation of the EventListener to respond to subscribed events
  /// @param event Valid Event
  void onEvent(Event &event);

  /// @brief Method to setup the roster list in the SelectLocoMenu when the roster has been received
  void setupSelectLocoMenu();

  /// @brief Set the loco being managed by the throttle screen
  /// @param loco Pointer to the loco object
  void setThrottleLoco(Loco *loco);

  /// @brief Notify the throttle screen an update has been received for the associated loco
  /// @param loco Pointer to the loco object
  void updateThrottleLoco(Loco *loco);

  /// @brief Notify the throttle screen of a track power update
  /// @param trackPower Track power state
  void updateThrottleTrackPower(TrackPower trackPower);

private:
  DisplayInterface *_displayInterface;
  ConnectionManager *_connectionManager;
  MenuManager *_menuManager;
  CommandStationClient *_commandStationClient;
  UserConfirmationInterface *_userConfirmationInterface;
  UserSelectionInterface *_userSelectionInterface;
  AppState _currentAppState;

  StartupScreen *_startupScreen;
  ThrottleScreen *_throttleScreen;
  ErrorScreen *_errorScreen;
  ProgressScreen *_progressScreen;

  /// @brief Show the startup screen and wait for user interaction before continuing
  void _handleStartupState();

  /// @brief Display the CommandStation menu and process user interaction to select one
  void _handleSelectCommandStationState();

  /// @brief Show the connection progress screen until a connection is made
  void _handleConnectCommandStationState();

  /// @brief Show the loco selection menu and process user interaction to select one
  void _handleSelectLocoState();

  /// @brief Show the throttle screen and process user interaction with the throttle
  void _handleThrottleState();

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

  /// @brief Join programming track to main and return to the Select Loco menu
  void _handleJoinProgTrack();

  /// @brief Set track power according to the provided EventType
  /// @param eventType Valid EventType
  void _handleSetTrackPower(EventType eventType);
};

#endif // APPORCHESTRATOR_H
