//
//    FILE: HC4067_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4067


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7);  //  no enable pin defined connect to GND.


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);
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

