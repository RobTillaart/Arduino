//
//    FILE: HC4053_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4053 3 x 2 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4053


#include "HC4053.h"

HC4053 mp(4, 5, 6, 8);  //  enable pin(8)

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4053 LIBRARY VERSION: ");
  Serial.println(HC4053_LIB_VERSION);
  Serial.println();
  delay(100);

  mp.setChannel(1);
  
  for (uint8_t ch = 0; ch < 2; ch ++)
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

  mp.setChannel(1);
  delay(100);

  start = micros();
  mp.setChannel(1);
  stop = micros();

  Serial.print("\nSetChannel: \t");
  Serial.println(stop - start);
  delay(100);

}


void loop()
{
}


//  -- END OF FILE --
