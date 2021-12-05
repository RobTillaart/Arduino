//
//    FILE: map2colour_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: map2colour demo
//    DATE: 2021-12-04
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"

map2colour mc;

// should be in increasing order; and 7 elements
float values[7] = { 0, 32, 64, 128, 256, 512, 1024 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // use the default colour map.
  mc.begin(values);

  for (float i = 0; i < 1024; i += 10)
  {
    uint32_t start = micros();
    uint32_t rgb = mc.map2RGB(i);
    uint32_t stop = micros();
    Serial.print(stop - start);   //  120 - 172 us
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
