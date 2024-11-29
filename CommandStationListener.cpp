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

#include "CommandStationListener.h"

CommandStationListener::CommandStationListener(EventManager *eventManager) : _eventManager(eventManager) {}

void CommandStationListener::receivedRosterList() {
  if (!_eventManager)
    return;
  EventData eventData;
  _eventManager->triggerEvent("ReceivedRosterList", eventData);
}

void CommandStationListener::receivedLocoUpdate(Loco *loco) {
  if (!_eventManager)
    return;
  EventData eventData(loco);
  _eventManager->triggerEvent("ReceivedLocoUpdate", eventData);
}

void CommandStationListener::receivedTrackPower(TrackPower powerState) {
  if (!_eventManager)
    return;
  EventData eventData(powerState);
  _eventManager->triggerEvent("ReceivedTrackPower", eventData);
}

void CommandStationListener::receivedReadLoco(int address) {
  if (!_eventManager)
    return;
  EventData eventData(address);
  _eventManager->triggerEvent("ReceivedReadLoco", eventData);
}
