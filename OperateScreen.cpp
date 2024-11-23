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

#include "Defines.h"
#include "OperateScreen.h"

OperateScreen::OperateScreen() {
  _speed = 0;
  _speedChanged = false;
  _direction = Direction::Forward;
  _directionChanged = false;
  _loco = nullptr;
}

void OperateScreen::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick:
    if (_speed == 0) {
      _directionChanged = true;
      if (_direction == Direction::Forward) {
        _direction = Direction::Reverse;
      } else {
        _direction = Direction::Forward;
      }
    } else {
      _speed = 0;
      _speedChanged = true;
    }
    break;
  case UserConfirmationAction::DoubleClick:
    CONSOLE.println("Toggle lights on|off");
    break;
  case UserConfirmationAction::LongPress:
    if (_speed > 0) {
      CONSOLE.println("Emergency stop");
    }
    break;
  default:
    _directionChanged = false;
    break;
  }
}

void OperateScreen::handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) {
  if (throttleInverted) {
    if (action == UserSelectionAction::Up) {
      action = UserSelectionAction::Down;
    } else if (action == UserSelectionAction::Down) {
      action = UserSelectionAction::Up;
    }
  }
  switch (action) {
  case UserSelectionAction::Up:
    if (_speed < 128) {
      _speed++;
      _speedChanged = true;
    }
    break;
  case UserSelectionAction::Down:
    if (_speed > 0) {
      _speed--;
      _speedChanged = true;
    }
    break;
  default:
    _speedChanged = false;
    break;
  }
}

void OperateScreen::drawScreen(DisplayInterface *display) {
  if (_speedChanged) {
    display->updateSpeed(_speed);
  }
  if (_directionChanged) {
    display->updateLocoDirection(_direction);
  }
  if (!display->needsRedraw())
    return;
  display->setNeedsRedraw(false);
  display->clear();
  display->updateSpeed(_speed);
  display->updateLocoDirection(Direction::Forward);
  display->updateLocoName("Dummy");
  display->updateTrackPowerState(TrackPower::PowerOff);
}

void OperateScreen::setLoco(Loco *loco) { _loco = loco; }

void OperateScreen::locoUpdateReceived(Loco *loco) {
  if (_loco != loco)
    return;
}

uint8_t OperateScreen::getSpeed() { return _speed; }
