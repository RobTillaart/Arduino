//
//    FILE: M5ANGLE8_led_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/M5ANGLE8


#include "m5angle8.h"


M5ANGLE8 MM;

void setup()
{
  Serial.begin(115200);
  Serial.print("M5ANGLE8_LIB_VERSION: ");
  Serial.println(M5ANGLE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  for (int ch = 0; ch < 8; ch++)
  {
    Serial.println(ch);
    MM.writeRGB(ch, 0, 0, 255, 100);
    delay(125);
    MM.writeRGB(ch, 0, 0, 0, 0);
    delay(125);
  }
}


//  -- END OF FILE --
