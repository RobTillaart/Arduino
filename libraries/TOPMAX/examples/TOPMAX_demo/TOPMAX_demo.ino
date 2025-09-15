//
//    FILE: TOPMAX_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: TOPMAX demo
//     URL: https://github.com/RobTillaart/TOPMAX


#include "TOPMAX.h"


TOPMAX tm(10);
uint32_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TOPMAX_LIB_VERSION: ");
  Serial.println(TOPMAX_LIB_VERSION);
  Serial.println();

  tm.fill(0);
  tm.reset();
}


void loop()
{
  int x = random(10000);

  Serial.print(cnt++);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  for (int i = 0; i < tm.count(); i++)
  {
    Serial.print(tm.getValue(i));
    Serial.print("\t");
  }
  Serial.println();

  tm.add(x);

  delay(100);
}


//  -- END OF FILE --

