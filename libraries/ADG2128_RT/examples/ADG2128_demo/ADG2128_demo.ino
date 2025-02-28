//
//    FILE: ADG2128_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ADG2128


#include "ADG2128.h"


ADG2128 sw(0x70);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG2128_LIB_VERSION: ");
  Serial.println(ADG2128_LIB_VERSION);

  Wire.begin();
  if (sw.begin() == false)
  {
    Serial.println("Error connecting to device");
    while(1);
  }
}


void loop()
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 12; col++)
    {
      sw.on(row, col);
    }
  }
  delay(100);
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 12; col++)
    {
      sw.off(row, col);
    }
  }
  delay(1000);
}


//  -- END OF FILE --
