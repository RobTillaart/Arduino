//
//    FILE: AD5144A_test_speed.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A


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

  for (uint32_t speed = 50000; speed < 850000; speed += 50000)
  {
    test_i2C_clock(speed);
  }
  Serial.println("done...");
}


void loop()
{
}


void test_i2C_clock(uint32_t clock)
{
  Wire.setClock(clock);

  Serial.println();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.println(clock);
  
  if (AD.isConnected() == false)
  {
    Serial.println("failed\n");
    return;
  }

  for (int p = 0; p < AD.pmCount(); p++)
  {
    for (int val = 0; val < 256; val++)
    {
      AD.write(p, val);
      if (AD.read(p) != val)
      {
        Serial.print("error:\t");
        Serial.print(p);
        Serial.print("\t");
        Serial.print(val);
        Serial.println();
      }
    }
  }
  Serial.println("ok\n");
}


// -- END OF FILE --
