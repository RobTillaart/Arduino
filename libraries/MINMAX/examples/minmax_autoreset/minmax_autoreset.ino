//
//    FILE: minmax_autoreset.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-10-14
//     URL: https://github.com/RobTillaart/minmax


#include "MINMAX.h"


MINMAX mm;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  mm.autoReset(10000);
}


void loop()
{
  int r = random(10001) - 5000;

  mm.add(r);
  if (mm.count() % 1000 == 0)
  {
    Serial.print(mm.count());
    Serial.print("\t");
    Serial.print(mm.minimum());
    Serial.print("\t");
    Serial.print(mm.maximum());
    Serial.print("\n");
  }
}



// -- END OF FILE --
