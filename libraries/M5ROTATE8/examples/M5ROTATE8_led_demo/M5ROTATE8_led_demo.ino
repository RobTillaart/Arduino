//
//    FILE: M5ROTATE8_led_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;

void setup()
{
  Serial.begin(115200);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  for (int ch = 0; ch < 9; ch++)
  {
    Serial.print(ch);
    MM.writeRGB(ch, 0, 0, 255);
    delay(MM.getAbsCounter(0));
    MM.writeRGB(ch, 0, 0, 0);
    delay(MM.getAbsCounter(0));
    Serial.println(MM.getAbsCounter(0));
  }
}


//  -- END OF FILE --
