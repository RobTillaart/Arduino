//
//    FILE: TOPMIN_duo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: TOPMAX demo
//     URL: https://github.com/RobTillaart/TOPMIN

//  demo tracking the top 20 and 
//  only from the top 3 we keep the time stamp


#include "TOPMIN.h"

//  saves about 60 bytes.
TOPMINext tm_small(3);
TOPMIN tm_large(20);

uint32_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TOPMIN_LIB_VERSION: ");
  Serial.println(TOPMIN_LIB_VERSION);
  Serial.println();
}


void loop()
{
  int x = random(10000);

  Serial.print(cnt++);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  for (int i = 0; i < tm_large.count(); i++)
  {
    Serial.print(tm_large.getValue(i));
    if (i < tm_small.size())
    {
      Serial.print(" (");
      Serial.print(tm_small.getTag(i));
      Serial.print(")");
    }
    Serial.print("\t");
  }
  Serial.println();

  tm_small.add(x, millis());
  tm_large.add(x);

  delay(100);
}


//  -- END OF FILE --
