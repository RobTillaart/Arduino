//
//    FILE: I2C_HC4067_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067
//
//  pin 8 to signal pin HC4067

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

  //  IO pin for multiplexer
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  Serial.println(mp.isEnabled());
  mp.enable();
  Serial.println(mp.isEnabled());
  mp.disable();
  Serial.println(mp.isEnabled());
  mp.enable();
  delay(1000);
}


void loop()
{
  // rotate over the channels
  for (uint8_t channel = 0; channel < 16; channel++)
  {
    mp.setChannel(channel);
    Serial.println(channel);
    delay(250);
  }

  //  Toggle the OUTPUT
  digitalWrite(8, digitalRead(8));
}


//  -- END OF FILE --
