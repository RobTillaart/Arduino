//
//    FILE: demo_displayTime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


// sketch will work correctly up to 99:99

#include "HT16K33.h"

HT16K33 seg(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  seg.begin();

  seg.displayOn();
  seg.setDigits(4);
}


void loop()
{
  static uint32_t last = 0;
  uint32_t now = millis();
  if (now != last)
  {
    last = now;
    uint32_t s = now / 1000;
    uint32_t t = (now - s * 1000) / 10;
    s = s % 100;
    // seg.displayTime(s, t);
    seg.displayTime(s, t, true, false);  // do not display leading zero.
    seg.displayColon(1);
  }
}


// -- END OF FILE --

