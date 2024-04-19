//
//    FILE: A1301_determineNoise.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo A1301 A1302 magnetometer.
//     URL: https://github.com/RobTillaart/A1301


#include "A1301.h"

A1301 mm(A0);

uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("A1301_LIB_VERSION: ");
  Serial.println(A1301_LIB_VERSION);

  mm.begin(5000, 1023);

  for (int t = 2; t < 20; t++)
  {
    Serial.print(t);
    Serial.print("\t");
    Serial.println(mm.determineNoise(t), 4);
  }
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
