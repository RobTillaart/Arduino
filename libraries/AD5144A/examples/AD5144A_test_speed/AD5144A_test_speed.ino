//
//    FILE: AD5144A_test_speed.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD5144A


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

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    for (int value = 0; value < 256; value++)
    {
      AD.write(potMeter, value);
      if (AD.read(potMeter) != value)
      {
        Serial.print("error:\t");
        Serial.print(potMeter);
        Serial.print("\t");
        Serial.print(value);
        Serial.println();
      }
    }
  }
  Serial.println("ok\n");
}


//  -- END OF FILE --
