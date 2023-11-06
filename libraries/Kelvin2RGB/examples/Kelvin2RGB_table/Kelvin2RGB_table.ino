//
//    FILE: Kelvin2RGB_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: generate table of values
//    DATE: 2020-07-29
//     URL: https://github.com/RobTillaart/Kelvin2RGB


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KELVIN2RGB_LIB_VERSION: ");
  Serial.println(KELVIN2RGB_LIB_VERSION);
  Serial.println();

  KRGB.begin();
  test();
}


void loop()
{
}


void test()
{
  float bright = 100.0;  //  change to 0.0
  while (bright <= 100.0)
  {
    bright += 5;
    for (uint32_t temp = 0; temp < 70000; temp += 200)
    {
      Serial.print(KRGB.temperature(), 0);
      Serial.print("\t");
      Serial.print(KRGB.brightness(), 0);
      Serial.print("\t");

      KRGB.convert_TH(temp, bright);
      Serial.print(KRGB.red(), 4);
      Serial.print("\t");
      Serial.print(KRGB.green(), 4);
      Serial.print("\t");
      Serial.print(KRGB.blue(), 4);
      Serial.print("\t");

      KRGB.convert_NB(temp, bright);
      Serial.print(KRGB.red(), 4);
      Serial.print("\t");
      Serial.print(KRGB.green(), 4);
      Serial.print("\t");
      Serial.print(KRGB.blue(), 4);
      Serial.print("\n");
    }
  }
}


//  -- END OF FILE --

