//
//    FILE: BH1750FVI_cont_high_res_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT
//
//  This sketch only works on platforms with a Wire1
//  e.g. ESP32 and RPIpico


#include "BH1750FVI.h"

BH1750FVI myLux(0x23, &Wire1);  //  explicit I2C bus.

uint32_t lastUpdate = 0;


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
  uint16_t interval = 100;
  if (millis() - lastUpdate >= interval)
  {
    lastUpdate += interval;
    float val = myLux.getLux();
    Serial.println(val, 1);
  }
}


//  -- END OF FILE --
