//
//    FILE: BH1750FVI_cont_high_res.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT
//
//  This is a minimal version, which can be optimized by
//  using mylux.getRaw() instead of myLux.getLux();  line 38
//  gain on UNO: ~350 bytes smaller


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
