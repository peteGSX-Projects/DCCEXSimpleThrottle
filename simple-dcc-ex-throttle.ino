#include <Arduino.h>
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"
#include "DCCEXFunctions.h"

void setup() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  disableJTAG();
#endif
  CONSOLE.begin(115200);
#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
  CLIENT.begin(115200);
#endif
  setupDisplay();
  setupButton();
  dccexProtocol.setLogStream(&CONSOLE);
  dccexProtocol.setDelegate(&dccexCallbacks);
  dccexProtocol.connect(&CLIENT);
  displayStartupInfo();
  // switchDisplay();
}

void loop() {
  dccexProtocol.check();
  getRoster();
  displayRuntime();
  processEncoder();
}

// Disabling JTAG is required to avoid pin conflicts on Bluepill
#if defined(ARDUINO_BLUEPILL_F103C8)
void disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}
#endif
