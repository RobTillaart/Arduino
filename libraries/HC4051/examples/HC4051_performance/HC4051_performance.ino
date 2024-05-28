//
//    FILE: HC4051_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4051 8 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4051


#include "HC4051.h"

HC4051 mp(4, 5, 6, 8);  //  enable pin(8)

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4051 LIBRARY VERSION: ");
  Serial.println(HC4051_LIB_VERSION);
  Serial.println();
  delay(100);

  mp.setChannel(10);
  
  for (uint8_t ch = 0; ch < 8; ch ++)
  {
    start = micros();
    mp.setChannel(ch);
    stop = micros();
    Serial.print("Channel ");
    Serial.print(ch);
    Serial.print(": \t");
    Serial.println(stop - start);
    delay(100);
  }

  mp.setChannel(5);
  delay(100);

  start = micros();
  mp.setChannel(5);
  stop = micros();

  Serial.print("\nSetChannel: \t");
  Serial.println(stop - start);
  delay(100);

}


void loop()
{
}


//  -- END OF FILE --
