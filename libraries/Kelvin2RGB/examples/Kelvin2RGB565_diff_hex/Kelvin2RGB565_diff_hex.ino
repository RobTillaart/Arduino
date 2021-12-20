//
//    FILE: Kelvin2RGB565_diff_hex.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - shows difference between 2 convert functions for the 565 16 bit coding
//    DATE: 2021-06-01
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//
// shows difference between the two calculations


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;
Kelvin2RGB KRGB2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  KRGB.begin();
  KRGB2.begin();

  test_difference();
}


void loop()
{
}


void test_difference()
{
  float bright = 100.0;
  for (uint32_t temp = 0; temp < 70000; temp += 200)
  {
    KRGB.convert_TH(temp, bright);
    KRGB2.convert_NB(temp, bright);

    Serial.print(KRGB.RGB565(), HEX);
    Serial.print("\t");
    Serial.print(KRGB2.RGB565(), HEX);
    Serial.print("\n");
  }
}


// -- END OF FILE --

