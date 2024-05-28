//
//    FILE: HC4052_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4052 2 x 4 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4052


#include "HC4052.h"

HC4052 mp(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4052 LIBRARY VERSION: ");
  Serial.println(HC4052_LIB_VERSION);
  Serial.println();

  delay(1000);
}


void loop()
{
  for (uint8_t channel = 0; channel < 4; channel++)
  {
    mp.setChannel(channel);
    Serial.println(analogRead(A0));
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
