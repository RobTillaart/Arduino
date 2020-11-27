//
//    FILE: demo_displayTime.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
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

  seg.begin();
  Wire.setClock(100000);
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
    seg.displayTime(s, t);
    seg.displayColon(1);
  }
}

// -- END OF FILE --
