//
//    FILE: M5ROTATE8_rel_counter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  for (int ch = 0; ch < 8; ch++)
  {
    Serial.print(MM.getRelCounter(ch));
    Serial.print("\t");
    Serial.print(MM.getKeyPressed(ch));
    Serial.print("\t");
    delay(125);
  }
  Serial.println();
}


//  -- END OF FILE --
