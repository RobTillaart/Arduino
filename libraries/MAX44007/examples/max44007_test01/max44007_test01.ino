//
//    FILE: Max44007_test01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//    DATE: 2022-01-04


#include "Wire.h"
#include "Max44007.h"

Max44007 myLux(0x5B);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);

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
    int err = myLux.getError();
    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.println(lux);
    }
  }
}


// -- END OF FILE --
