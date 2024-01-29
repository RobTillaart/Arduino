//
//    FILE: AD5144A_test_preload_sync.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD5144A


//  connect the AD5144A to a multichannel scope
//  to verify the potentiometers change at the same time 


#include "AD5144A.h"

//  select the right type
//  adjust address
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

  for (int value = 0; value < 256; value += 17)
  {
    //  loop over all channels / potmeters
    for (uint8_t potMeter = 0; potMeter < AD.pmCount(); potMeter++)  
    {
      AD.preload(potMeter, value);
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

  for (int value = 0; value < 256; value += 17)
  {
    AD.preloadAll(value);
    AD.sync(0x0F);
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
