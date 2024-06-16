//
//    FILE: M5ROTATE8_button_mask.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo firmware V2 function
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
  //  Note: mask is inverted register.
  uint8_t mask = MM.getButtonChangeMask();
  if (mask != 0)
  {
    for (int button = 0; button < 8; button++)
    {
      Serial.print("Button ");
      Serial.print(button);
      Serial.print(" has state ");
      Serial.println((mask & (1 << button)) > 0);
    }
  }
}


//  -- END OF FILE --
