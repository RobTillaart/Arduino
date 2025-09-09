//
//    FILE: M5ANGLE8_led_follow.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo (works well with build in plotter)
//     URL: https://github.com/RobTillaart/M5ANGLE8


#include "m5angle8.h"

M5ANGLE8 MM;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M5ANGLE8_LIB_VERSION: ");
  Serial.println(M5ANGLE8_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  uint16_t val;
  for (int ch = 0; ch < 8; ch++)
  {
    val = MM.analogRead(ch);
    MM.writeRGB(ch, val / 16, 0, 0, 50);
    Serial.print(val);
    Serial.print("\t");
    delay(1);
  }
  val = MM.inputSwitch();
  MM.writeRGB(8, 0, 0, val * 255, 50);
  Serial.print("\n");
  delay(0);
}


//  -- END OF FILE --
