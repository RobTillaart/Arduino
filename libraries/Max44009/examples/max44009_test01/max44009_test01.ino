//
//    FILE: max44009_test01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: demo of max44009 library
//    DATE: 2015-08-06
//
// Released to the public domain
//

#include "Wire.h"
#include "Max44009.h"

Max44009 myLux(0xCB);         // default addr

uint32_t lastDisplay = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start max44009_test01 : ");
  Serial.println(MAX44009_LIB_VERSION);

  Wire.begin();

}

void loop()
{
  if (millis() - lastDisplay >= 1000)
  {
    lastDisplay += 1000;
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

// END OF FILE
