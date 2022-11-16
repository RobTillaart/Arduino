//
//    FILE: max44009_test01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of max44009 library
//    DATE: 2015-08-06
//
//      breakout MAX44009 / GY-49
//
//          +--------+
//      VCC |o       |
//      GND |o       |
//      SCL |o      o| ADDRESS
//      SDA |o      o| -INT
//          +--------+
//
//  ADDRESS:
//  0 = 0x4A
//  1 = 0x4B


#include "Wire.h"
#include "Max44009.h"

Max44009 myLux(0x4A);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start max44009_test01 : ");
  Serial.println(MAX44009_LIB_VERSION);

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
      Serial.println(lux, 3);
    }
  }
}


// -- END OF FILE --
