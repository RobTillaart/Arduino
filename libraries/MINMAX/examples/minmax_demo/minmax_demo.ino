//
//    FILE: minmax_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/minmax


#include "MINMAX.h"


MINMAX mm;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MINMAX_LIB_VERSION: ");
  Serial.println(MINMAX_LIB_VERSION);
  Serial.println();

  mm.reset();
}


void loop()
{
  int r = random(1000) - 500;

  mm.add(r);
  if (mm.count() % 100 == 0)
  {
    Serial.print(mm.count());
    Serial.print("\t");
    Serial.print(mm.minimum());
    Serial.print("\t");
    Serial.print(mm.maximum());
    Serial.print("\t");
    Serial.print(mm.lastMin());
    Serial.print("\t");
    Serial.print(mm.lastMax());
    Serial.print("\n");
    mm.reset();
  }
}


//  -- END OF FILE --
