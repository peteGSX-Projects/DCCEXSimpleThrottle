#ifndef DEFINES_H
#define DEFINES_H

#define CONNECT_RETRIES 20

#define ENCODER_DT PC14
#define ENCODER_CLK PC15
#define ENCODER_SW PA0

#define OLED_FONT System5x7

#define OLED_TYPE &SH1106_128x64
#define CS_PIN PA4
#define DC_PIN PA3

#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
#define CLIENT Serial1
#else
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
#define CLIENT Serial
#endif

#endif
