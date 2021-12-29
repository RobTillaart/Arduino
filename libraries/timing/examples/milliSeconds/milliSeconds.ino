//
//    FILE: milliSeconds.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/timing


#include "timing.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  delay(10);

  milliSeconds mis;     // starts at zero
  for (uint32_t i = 0; i < 1000; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(i*i);
  }
  uint32_t x = mis.now();
  Serial.print("milliseconds:\t");
  Serial.println(x);

  mis.set(0);     // starts at zero
  for (uint32_t i = 0; i < 1000; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(i*i);
  }
  x = mis.now();
  Serial.print("milliseconds:\t");
  Serial.println(x);

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

