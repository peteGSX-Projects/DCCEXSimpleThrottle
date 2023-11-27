#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include "defines.h"
#include "EncoderFunctions.h"

extern SSD1306AsciiSpi oled;

void setupDisplay();
void displayStartupInfo();
void switchDisplay();
void displayRuntime();
void displaySpeed();
void displayDirection();
void displayAddress();
void displayMenu();
void scrollMenu();

#endif
