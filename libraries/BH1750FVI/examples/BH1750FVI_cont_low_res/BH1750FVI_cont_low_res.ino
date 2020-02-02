//
//    FILE: BH1750FVI_cont_low_res.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of BH1750FVI lux scanner library
//    DATE: 2020-02-02
//
// Released to the public domain
//

#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

uint32_t lastUpdate = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.println();

  Wire.begin();

  myLux.powerOn();
  myLux.setContLowRes();
}

void loop()
{
  int interval = 100;
  if (millis() - lastUpdate >= interval)
  {
    lastUpdate += interval;
    float val = myLux.getLux();
    Serial.println(val, 1);
  }

}

// END OF FILE
