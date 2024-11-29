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
#include "CommandStationClient.h"
#include "CommandStationDetails.h"
#include "CommandStationListener.h"
#include "ConnectionManager.h"
#include "Defines.h"
#include "MenuManager.h"
#include "RotaryEncoder.h"
#include "U8G2SH1106Display.h"

/// @brief Class to perform all application configuration on startup
/// All interfaces, menus, and other application objects are created within this class
class AppConfiguration {
public:
  /// @brief Constructor for the app configuration object
  AppConfiguration();

  /// @brief Start all associated user interfaces and instantiate all objects
  /// EventManager registrations are done here
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

  /// @brief Get the connection manager
  /// @return Pointer to the connection manager
  ConnectionManager *getConnectionManager();

  /// @brief Get the menu manager
  /// @return Pointer to the menu manager
  MenuManager *getMenuManager();

  /// @brief Get the CommandStation client
  /// @return Pointer to the CommandStation client
  CommandStationClient *getCommandStationClient();

private:
  UserConfirmationInterface *_userConfirmationInterface;
  UserSelectionInterface *_userSelectionInterface;
  DisplayInterface *_displayInterface;
  ConnectionManager *_connectionManager;
  MenuManager *_menuManager;
  CommandStationListener *_commandStationListener;
  CommandStationClient *_commandStationClient;
  AppOrchestrator *_appOrchestrator;

#ifdef WIFI_ENABLED
  uint8_t _commandStationCount;
  CommandStationDetails _commandStationList[COMMANDSTATION_COUNT];

  /// @brief Initialise the array of CommandStationDetails to create the server menu list
  void _initialiseCommandStationArray();

  /// @brief Convert the provided IP address to an IP address object
  /// @param ipAddressString Pointer to the char array containing the IP address
  /// @return IPAddress object
  IPAddress _convertIP(const char *ipAddressString);
#endif // WIFI_ENABLED

  /// @brief Disabling JTAG is required to avoid pin conflicts when using Bluepill
#if defined(ARDUINO_BLUEPILL_F103C8)
  void _disableJTAG();
#endif // BLUEPILL
};

#endif // APPCONFIGURATION_H
