//   https://github.com/RobTillaart/TinyKT0803/

#include <TinyKT0803.h>
#include <Tiny4kOLED.h>

TinyKT0803 FM_SEND;

void oledInit() {
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.clear();
  oled.on();
}

void oledFreq() {
  oled.clear();
  oled.setFont(FONT8X16P);
  oled.setCursor(20, 2);
  oled.print(FM_SEND.getFrequency());
}

void setup() {
  TinyWireM.begin();
  //  give I2C time to initialize (hard coded here)
  delay(500);

  FM_SEND.begin();
  FM_SEND.setFrequency(97.00);
  FM_SEND.setMute(false);

  oledInit();
  oledFreq();
}

void loop() {
  //
}