//
//    FILE: minmax_demot.ino
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
    Serial.print("\n");
    mm.reset();
  }
}



// -- END OF FILE --
