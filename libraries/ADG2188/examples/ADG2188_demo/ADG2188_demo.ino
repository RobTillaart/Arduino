//
//    FILE: ADG2188_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ADG2188


#include "ADG2188.h"


ADG2188 sw(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG2188_LIB_VERSION: ");
  Serial.println(ADG2188_LIB_VERSION);

  Wire.begin();
  if (sw.begin() == false)
  {
    Serial.println("Error connecting to device");
    while(1);
  }
}


void loop()
{
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      sw.on(x,y);
    }
  }
  delay(100);
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      sw.off(x,y);
    }
  }
  delay(1000);
}


//  -- END OF FILE --
