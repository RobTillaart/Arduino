//
//    FILE: minmax_new.ino
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

  mm.setAutoResetCount(10000);
}


void loop()
{
  int r = random(10001) - 5000;

  if (mm.add(r) != 0x00)  //  changed minimum or maximum or reset
  {
    Serial.print(mm.count());
    Serial.print("\t");
    Serial.print(mm.minimum());
    Serial.print("\t");
    Serial.print(mm.maximum());
    Serial.print("\n");
  }
}


//  -- END OF FILE --

