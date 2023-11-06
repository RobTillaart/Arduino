//
//    FILE: Kelvin2RGB_difference.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - shows difference between 2 convert functions.
//    DATE: 2020-07-29
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
    Serial.print(KRGB.blue() - KRGB2.blue());
    Serial.print("\t");
    Serial.print(KRGB.red() - KRGB2.red());
    Serial.print("\t");
    Serial.print(KRGB.green() - KRGB2.green());
    Serial.print("\n");
  }
}


//  -- END OF FILE --

