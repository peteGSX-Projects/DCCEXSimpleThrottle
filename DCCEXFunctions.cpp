#include <Arduino.h>
#include "DCCEXFunctions.h"

DCCEXProtocol dccexProtocol;
DCCEXCallbacks dccexCallbacks;

uint8_t connectionRetries=CONNECT_RETRIES;
unsigned long retryDelay=1000;
unsigned long lastRetry=0;
bool gotRoster=false;
bool retrievalDisplayed=false;
bool errorDisplayed=false;
bool setupScreen=false;
int col=0;
int row=2;

void getRoster() {
  if (!dccexProtocol.receivedLists() && connectionRetries>0) {
    if (!retrievalDisplayed) {
      oled.clear();
      oled.setCursor(0, 0);
      oled.print(F("Retrieving roster..."));
      retrievalDisplayed=true;
    } else if (!dccexProtocol.receivedLists() && millis()-lastRetry>retryDelay && connectionRetries>0) {
      lastRetry=millis();
      connectionRetries--;
      oled.setCursor(col, row);
      oled.print(F("."));
      col=col+5;
      if (col>120) {
        row++;
        col=0;
      }
    }
    dccexProtocol.getLists(true, false, false, false);
  } else if (!dccexProtocol.receivedLists() && connectionRetries==0 && !errorDisplayed) {
    oled.clear();
    oled.setCursor(0, 0);
    oled.print(F("Could not retrieve roster"));
    errorDisplayed=true;
  } else if (dccexProtocol.receivedLists() && !setupScreen) {
    setupScreen=true;
    populateMenu();
    switchDisplay();
  }
}
