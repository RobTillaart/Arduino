//
//    FILE: M5ROTATE8_set_abs_counter.ino
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
  MM.resetAll();
}


void loop()
{
  for (int ch = 0; ch < 8; ch++)
  {
    Serial.print(MM.getAbsCounter(ch));
    Serial.print("\t");
    uint8_t x = MM.getKeyPressed(ch);
    Serial.print(x);
    Serial.print("\t");
    if (x == 1)  //  if key pressed randomize
    {
      MM.setAbsCounter(ch, random(1000) - 500);
    }
    delay(10);
  }
  uint8_t clr = MM.inputSwitch();  //  use as clear flag
  Serial.print(clr);
  Serial.print("\n");
  if (clr == 1)
  {
    for (int ch = 0; ch < 8; ch++)
    {
      MM.setAbsCounter(ch, 0);
    }
  }

  delay(20);
}


//  -- END OF FILE --
