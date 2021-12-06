//
//    FILE: map2colour_map2_565.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: map2colour demo
//    DATE: 2021-12-05
//     URL: https://github.com/RobTillaart/map2colour


#include "Arduino.h"
#include "map2colour.h"


map2colour mc;

// should be in increasing order
float values[7] = { 0, 32, 64, 128, 256, 512, 1024 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // load the values array
  mc.begin(values);

  // show the interpolating
  for (float i = 0; i < 1024; i += 10)
  {
    uint16_t rgb = mc.map2_565(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(rgb, HEX);
  }
  Serial.println();
}


void loop()
{
  int x = analogRead(0);          // UNO returns between 0..1023; adapt if needed.
  uint32_t rgb = mc.map2_565(x);
  Serial.print(x);
  Serial.print("\t");
  Serial.println(rgb, HEX);
  delay(100);
}


// -- END OF FILE --
