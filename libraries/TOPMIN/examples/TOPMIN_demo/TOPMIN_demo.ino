//
//    FILE: TOPMIN_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: TOPMIN demo
//     URL: https://github.com/RobTillaart/TOPMIN


#include "TOPMIN.h"


TOPMIN tm(10);
uint32_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TOPMIN_LIB_VERSION: ");
  Serial.println(TOPMIN_LIB_VERSION);
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
