//
//    FILE: Max44007_test01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//     URL: https://github.com/RobTillaart/MAX44007


#include "Max44007.h"


Max44007 myLux(0x5B);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Wire.setClock(100000);
}


void loop()
{
  uint32_t interval = 1000;

  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    float lux = myLux.getLux();
    int error = myLux.getError();
    if (error != 0)
    {
      Serial.print("Error:\t");
      Serial.println(error);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.println(lux, 3);
    }
  }
}


//  -- END OF FILE --
