//
//    FILE: HC4067_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7, 8);  //  explicitly set enable pin (8)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);

  Serial.println(mp.isEnabled());
  mp.enable();
  Serial.println(mp.isEnabled());
  mp.disable();
  Serial.println(mp.isEnabled());

  delay(1000);
}


void loop()
{
  for (uint8_t channel = 0; channel < 16; channel++)
  {
    mp.enable();
    mp.setChannel(channel);
    Serial.println(analogRead(A0));
    mp.disable();
    delay(100);
  }
}


//  -- END OF FILE --
