# Simple DCC-EX Throttle

This is a very simple throttle that communicates with a DCC-EX EX-CommandStation via a serial interface and can control one DCC locomotive.

## Hardware

Bluepill

128 x 64 OLED

Rotary encoder

## Operation

On start up, no locomotive will be selected, and the roster list retrieved from the EX-CommandStation will be displayed.

Use the rotary encoder to scroll down the roster list and press the encoder's button once to select a locomotive.

Once selected, use the encoder to increase and decrease the speed.

When speed is 0 (zero), press the encoder button once to change direction.

## Select a different locomotive

When speed is 0 (zero), double click the encoder button, and the roster list will once again be displayed.

Use the encoder to scroll through the roster list and press the encoder's button once to select a locomotive.

Once selected, the previous locomotive is forgotten, and the currently selected locomotive is controlled instead.

## Turn track power on and off

When speed is 0 (zero) and a locomotive is selected, hold the encoder button down for more than half a second.

If track power is off, it will be turned on, and if turned on, it will be turned off.

## Emergency stop

When a locomotive is selected and speed is more than zero (0), hold the encoder down for more than half a second.

An emergency stop will be sent to the EX-CommandStation.
