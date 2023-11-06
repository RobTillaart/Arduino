//
//    FILE: Kelvin2RGB_diff_hex.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - shows difference between 2 convert functions for the 565 16 bit coding
//    DATE: 2021-06-01
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//
//       best viewed in plotter.


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;
Kelvin2RGB KRGB2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KELVIN2RGB_LIB_VERSION: ");
  Serial.println(KELVIN2RGB_LIB_VERSION);
  Serial.println();

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

    Serial.print(KRGB.RGB(), HEX);
    Serial.print("\t");
    Serial.print(KRGB2.RGB(), HEX);
    Serial.print("\n");
  }
}


//  -- END OF FILE --

