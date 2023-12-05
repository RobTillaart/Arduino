//
//    FILE: demo_cache.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 seg(0x70);

uint32_t start, stop, d1, d2;


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
  seg.setBrightness(2);
  seg.displayClear();
  seg.setBlink(0);
}


void loop()
{
  // Note: UNO fails for speed above 850K
  //       UNO 750K and 800K are using same clock divider
  Serial.println("\nSPEED \tNOCACHE \tms/call \tCACHE\t\tms/call \tRATIO");
  for (uint32_t sp = 100000; sp < 900000; sp += 50000)
  {
    test_cache(sp);
  }
  Serial.println();
}


void test_cache(uint32_t speed)
{
  Wire.setClock(speed);
  Serial.print(speed);
  Serial.print("\t");
  seg.cacheOff();
  start = millis();
  for (int16_t counter = -999; counter < 10000; counter+=10)
  {
    seg.displayInt(counter);
  }
  d1 = millis() - start;
  Serial.print(d1);
  Serial.print("\t\t");
  Serial.print(d1 / 1100.0, 3);
  Serial.print("\t\t");
  delay(100);

  seg.cacheOn();
  start = millis();
  for (int16_t counter = -999; counter < 10000; counter+=10)
  {
    seg.displayInt(counter);
  }
  d2 = millis() - start;
  Serial.print(d2);
  Serial.print("\t\t");
  Serial.print(d2 / 1100.0, 3);
  Serial.print("\t\t");
  Serial.println(1.0 * d1 / d2, 3);
  delay(1000);
}


// -- END OF FILE --

