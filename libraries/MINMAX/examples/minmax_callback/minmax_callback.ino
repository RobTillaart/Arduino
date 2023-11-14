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
  mm.addCallBack(display);
}


void loop()
{
  int r = random(10001) - 5000;
  mm.add(r);
}


void display()
{
  Serial.print(mm.count());
  Serial.print("\t");
  Serial.print(mm.minimum());
  Serial.print("\t");
  Serial.print(mm.maximum());
  Serial.print("\n");
}


//  -- END OF FILE --
