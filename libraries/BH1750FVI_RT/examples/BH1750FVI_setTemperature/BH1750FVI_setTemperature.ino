//
//    FILE: BH1750FVI_setTemperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT


#include "BH1750FVI.h"

BH1750FVI myLux(0x23);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.println();

  Wire.begin();

  myLux.powerOn();
  myLux.setContHighRes();
}


void loop()
{
  for (int t = -60; t < 100; t += 10)
  {
    myLux.setTemperature(t);
    float val = myLux.getLux();

    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux.getTemperature());
    Serial.print("\t");
    Serial.println();
    delay(20);
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --

