//
//    FILE: M5ANGLE8_analogRead4.ino
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
    Serial.print(MM.analogRead(ch, 4));  //  low resolution 0..15
    Serial.print("\t");
    delay(1);
  }
  Serial.print(MM.inputSwitch());
  Serial.print("\n");
  delay(10);
}


//  -- END OF FILE --
