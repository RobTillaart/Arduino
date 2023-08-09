//
//    FILE: M5ANGLE8_analogRead8_reverse.ino
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

  MM.setReverse(true);
}


void loop()
{
  for (int ch = 0; ch < 8; ch++)
  {
    Serial.print(MM.analogRead(ch, 8));
    Serial.print("\t");
    delay(1);
  }
  int x = MM.inputSwitch();
  Serial.print(x);
  Serial.print("\n");
  MM.setReverse(x);
  delay(10);
}


//  -- END OF FILE --
