//
//    FILE: I2C_HC4067_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067


#include "I2C_HC4067.h"

I2C_HC4067 mp(0x38);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_HC4067_LIB_VERSION: ");
  Serial.println(I2C_HC4067_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);
  mp.begin();
  delay(100);
}


void loop()
{
  for (uint8_t channel = 0; channel < 16; channel++)
  {
    mp.setChannel(channel);
    Serial.print(analogRead(A0));
    Serial.print("\t");
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
