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
#include "ThrottleScreen.h"

ThrottleScreen::ThrottleScreen(DCCEXProtocol *dccexProtocolClient, uint8_t throttleStep, uint8_t throttleStepFaster,
                               uint8_t throttleStepFastest)
    : _dccexProtocolClient(dccexProtocolClient), _throttleStep(throttleStep), _throttleStepFaster(throttleStepFaster),
      _throttleStepFastest(throttleStepFastest) {
  _speed = 0;
  _speedChanged = false;
  _direction = Direction::Forward;
  _directionChanged = false;
  _loco = nullptr;
  _trackPower = TrackPower::PowerUnknown;
  _trackPowerChanged = false;
  _speedUpdateDelay = 500;
  _lastSpeedUpdate = 0;
}

void ThrottleScreen::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick:
    if (_speed == 0) {
      _directionChanged = true;
      if (_direction == Direction::Forward) {
        _direction = Direction::Reverse;
        _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
      } else {
        _direction = Direction::Forward;
        _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
      }
    } else {
      _dccexProtocolClient->setThrottle(_loco, 0, _direction);
    }
    break;
  case UserConfirmationAction::DoubleClick:
    _toggleLights();
    break;
  case UserConfirmationAction::LongPress:
    if (_speed > 0) {
      _dccexProtocolClient->emergencyStop();
    } else {
      _toggleTrackPower();
    }
    break;
  default:
    break;
  }
}

void ThrottleScreen::handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) {
  if (throttleInverted) {
    if (action == UserSelectionAction::Up) {
      action = UserSelectionAction::Down;
    } else if (action == UserSelectionAction::UpFaster) {
      action = UserSelectionAction::DownFaster;
    } else if (action == UserSelectionAction::UpFastest) {
      action = UserSelectionAction::DownFastest;
    } else if (action == UserSelectionAction::Down) {
      action = UserSelectionAction::Up;
    } else if (action == UserSelectionAction::DownFaster) {
      action = UserSelectionAction::UpFaster;
    } else if (action == UserSelectionAction::DownFastest) {
      action = UserSelectionAction::UpFastest;
    }
  }
  uint8_t minSpeed = 0;
  uint8_t maxSpeed = 127;
  uint8_t changeStep = 0;
  bool speedUp = false;
  switch (action) {
  case UserSelectionAction::Up: {
    changeStep = _throttleStep;
    speedUp = true;
    break;
  }
  case UserSelectionAction::UpFaster: {
    changeStep = _throttleStepFaster;
    speedUp = true;
    break;
  }
  case UserSelectionAction::UpFastest: {
    changeStep = _throttleStepFastest;
    speedUp = true;
    break;
  }
  case UserSelectionAction::Down: {
    changeStep = _throttleStep;
    speedUp = false;
    break;
  }
  case UserSelectionAction::DownFaster: {
    changeStep = _throttleStepFaster;
    speedUp = false;
    break;
  }
  case UserSelectionAction::DownFastest: {
    changeStep = _throttleStepFastest;
    speedUp = false;
    break;
  }
  default:
    break;
  }
  if (speedUp && changeStep > 0) {
    if (maxSpeed - _speed >= changeStep) {
      _speed += changeStep;
      _speedChanged = true;
    } else if (_speed < maxSpeed) {
      _speed += 1;
      _speedChanged = true;
    }
  } else if (changeStep > 0) {
    if (minSpeed + changeStep <= _speed) {
      _speed -= changeStep;
      _speedChanged = true;
    } else if (_speed > 0) {
      _speed -= 1;
      _speedChanged = true;
    }
  }
  if (_speedChanged) {
    _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
  }
}

void ThrottleScreen::drawScreen(DisplayInterface *display) {
  if (millis() - _lastSpeedUpdate > _speedUpdateDelay) {
    _lastSpeedUpdate = millis();
    _speed = _loco->getSpeed();
    _speedChanged = true;
  }
  if (_speed == 127) {
    _speed = 126; // bit ugly, but prevents displaying 127 momentarily
  }
  display->displayThrottleScreen(_loco->getName(), _speed, _loco->getDirection(), _trackPower, _speedChanged,
                                 _directionChanged, _trackPowerChanged);
  _speedChanged = false;
  _directionChanged = false;
  _trackPowerChanged = false;
}

void ThrottleScreen::setLoco(Loco *loco) { _loco = loco; }

void ThrottleScreen::locoUpdateReceived(Loco *loco) {
  if (_loco != loco)
    return;
  _directionChanged = true;
  if (_loco->getDirection() != _direction) {
    _direction = _loco->getDirection();
  }
}

uint8_t ThrottleScreen::getSpeed() { return _speed; }

void ThrottleScreen::trackPowerUpdateReceived(TrackPower trackPower) {
  if (trackPower != _trackPower) {
    _trackPower = trackPower;
    _trackPowerChanged = true;
  }
}

void ThrottleScreen::requestLocoUpdate() { _dccexProtocolClient->requestLocoUpdate(_loco->getAddress()); }

void ThrottleScreen::requestTrackPowerUpdate() { _dccexProtocolClient->requestServerVersion(); }

void ThrottleScreen::_toggleTrackPower() {
  if (_trackPower == TrackPower::PowerOff || _trackPower == TrackPower::PowerUnknown) {
    _dccexProtocolClient->powerOn();
  } else {
    _dccexProtocolClient->powerOff();
  }
}

void ThrottleScreen::_toggleLights() {
  int function = 0;
  if (_dccexProtocolClient->isFunctionOn(_loco, function)) {
    _dccexProtocolClient->functionOff(_loco, function);
  } else {
    _dccexProtocolClient->functionOn(_loco, function);
  }
}
