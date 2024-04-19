//
//    FILE: A1301_test.ino
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

  for (float r = 505; r < 515; r += 0.5)
  {
    test(r);
  }

  Serial.println("\ndone...");
}


void loop()
{
}

void test(float raw)
{
  Serial.print(raw);
  Serial.print("\t");
  Serial.print(mm.readExt(raw));
  Serial.print("\t");
  Serial.print(mm.isNull());
  Serial.print("\t");
  Serial.print(mm.isNorth());
  Serial.print("\t");
  Serial.print(mm.isSouth());
  Serial.print("\t");
  Serial.print(mm.isRising());
  Serial.print("\t");
  Serial.print(mm.isFalling());
  Serial.print("\t");
  Serial.print(mm.isSaturated());
  Serial.print("\t");
  Serial.print(mm.prevGauss());
  Serial.print("\t");
  Serial.print(mm.lastGauss());
  Serial.print("\t");
  Serial.print(mm.deltaGauss());
  Serial.print("\t");
  Serial.print(mm.saturationLevel());
  Serial.print("\n");
}


//  -- END OF FILE --
