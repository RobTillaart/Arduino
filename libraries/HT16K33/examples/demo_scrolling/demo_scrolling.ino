//
//    FILE: demo_scrolling.ino
//  AUTHOR: Rob Tillaart, DeflateAwning
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 display(0x70);

uint32_t start = 0;

void display_scrolling_press_start(uint32_t idle_start_time_ms) 
{
  const int msg_len = 14;
  int offset = ((millis() - idle_start_time_ms) / 500) % (msg_len);

  const uint8_t SEG_PRESS_START[] = {
    SEG_A | SEG_B | SEG_F | SEG_E | SEG_G,           // P
    SEG_E | SEG_G,                                   // r
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
    SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,           // S
    SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,           // S
    SEG_NONE,                                        // [space]
    SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,           // S
    SEG_F | SEG_E | SEG_G | SEG_D,                   // t
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
    SEG_E | SEG_G,                                   // r
    SEG_F | SEG_E | SEG_G | SEG_D,                   // t
    SEG_NONE,                                        // [space]
    SEG_NONE,                                        // [space]
    SEG_NONE                                         // [space]
  };
  uint8_t seg1_data[] = {SEG_D, SEG_D, SEG_D, SEG_D};
  // uint8_t seg2_data[] = {SEG_D, SEG_D, SEG_D, SEG_D};

  for (int i = 0; i < 4; i++) {
    seg1_data[i] = SEG_PRESS_START[(i + offset) % msg_len];
    // seg2_data[i] = SEG_PRESS_START[(i+offset+5)%msg_len];
  }

  display.displayRaw(seg1_data);
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  display.begin();

  display.displayOn();
  display.setBrightness(2);
  display.displayClear();

  start = millis();
}


void loop()
{
  display_scrolling_press_start(start);
  delay(100);
}


//  -- END OF FILE --
