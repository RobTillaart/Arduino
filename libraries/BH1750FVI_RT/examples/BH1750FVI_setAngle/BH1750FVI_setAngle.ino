//
//    FILE: BH1750FVI_setAngle.ino
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
  for (int x = -90; x < 90; x += 1)
  {
    myLux.setAngle(x);
    float val = myLux.getLux();

    Serial.print(val, 1);
    Serial.print("\t");
    Serial.print(myLux.getAngle());
    Serial.print("\t");
    Serial.println();
    delay(20);
  }
  Serial.println();
}


//  -- END OF FILE --
