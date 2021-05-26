//
//    FILE: AD5144A_test_preload_sync.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-05-04
//     URL: https://github.com/RobTillaart/AD5144A


// connect the AD5144A to a multichannel scope
// to verify the potmeters change at the same time 


#include "AD5144A.h"

// select the right type
// adjust address
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (AD.begin() == false)
  {
    Serial.println("device not found");
    return;
  }

  test_preload();
  delay(1000);
  test_preloadAll();

  Serial.println("done...");
}


void loop()
{
}


void test_preload()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int val = 0; val < 256; val += 17)
  {
    for (uint8_t ch = 0; ch < AD.pmCount(); ch++) // all channels
    {
      AD.preload(ch, val);
    }
    AD.sync(0x0F);
    delay(100);
  }
  Serial.println();
}


void test_preloadAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int val = 0; val < 256; val += 17)
  {
    AD.preloadAll(val);
    AD.sync(0x0F);
    delay(100);
  }
  Serial.println();
}


// -- END OF FILE --
