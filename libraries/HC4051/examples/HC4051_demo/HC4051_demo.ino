//
//    FILE: HC4051_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4051 8 channel (simple) multiplexer


#include "HC4051.h"

HC4051 mp(4, 5, 6);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4051 LIBRARY VERSION: ");
  Serial.println(HC4051_LIB_VERSION);
  Serial.println();

  delay(1000);
}


void loop()
{
  for (uint8_t channel = 0; channel < 8; channel++)
  {
    mp.setChannel(channel);
    Serial.println(analogRead(A0));
    delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
