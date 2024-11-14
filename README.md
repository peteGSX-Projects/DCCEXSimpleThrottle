# DCC-EX Simple Throttle

This is a very simple throttle that communicates with a DCC-EX EX-CommandStation via a serial or WiFi interface and can control one DCC locomotive and perform some other basic activities.

Selecting a locomotive to control requires a roster to be configured in the EX-CommandStation, or alternatively the DCC address can be acquired by placing the locomotive on the programming track and opting to read the address from there instead.

There is some brief information in this README, however for the full documentation refer to [Pete's Pages](https://petegsx-projects.github.io/simple-throttle/index.html).

## Hardware

- Either an STMicroelectronics F103C8 based Bluepill or Wemos D1 Mini/Lolin 32 Lite
- 128 x 64 SH1106 based I2C or SPI OLED
- Rotary encoder (eg. KY-040)

## Installation and configuration

The software in this repository has been written to take advantage of VSCode and PlatformIO, and will automatically obtain the required libraries:

- DCCEX/DCCEXProtocol
- olikraus/U8g2

If using a Bluepill and serial connection, no user configuration should be required.

If using a Wemos D1 Mini or Lolin32 Lite, you will need to update the WiFi and CommandStation connection parameters by copying myConfig.example.h to myConfig.h and editing it as required.

If you wish to use the Arduino IDE, you will need to ensure the appropriate STM32 and/or Espressif board support is installed along with the above libraries.
