//
//    FILE: TOPMAXext_millis.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: TOPMAX demo
//     URL: https://github.com/RobTillaart/TOPMAX


#include "TOPMAX.h"


TOPMAXext tme(5);
uint32_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TOPMAX_LIB_VERSION: ");
  Serial.println(TOPMAX_LIB_VERSION);
  Serial.println();

  tme.fill(0, 0);
  tme.reset();
}


void loop()
{
  int x = random(10000);

  Serial.print(cnt++);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  for (int i = 0; i < tme.count(); i++)
  {
    Serial.print(tme.getValue(i));
    Serial.print(":(");
    Serial.print(tme.getTag(i));
    Serial.print(")\t");
  }
  Serial.println();

  tme.add(x, millis());

  delay(random(200));
}


//  -- END OF FILE --
