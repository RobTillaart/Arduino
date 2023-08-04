//
//    FILE: M5ANGLE8_analog12_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo (works well with build in plotter)
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
    uint16_t val = MM.analogRead(ch);
    MM.writeRGB(ch, val / 16, 0, 0, 50);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.print("\n");
  delay(20);
}


//  -- END OF FILE --
