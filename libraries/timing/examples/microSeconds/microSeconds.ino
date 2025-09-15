//
//    FILE: microSeconds.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/timing


#include "timing.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TIMING_LIB_VERSION: ");
  Serial.println(TIMING_LIB_VERSION);
  Serial.println();
  delay(10);

  uint32_t z = micros();
  microSeconds ms;  //  starts at zero
  uint64_t big = fibonaci(91);  //  91 is the max!
  uint32_t x = micros();
  uint32_t y = ms.now();
  //  do it the long way
  Serial.print("micros():\t");
  Serial.print(x);
  Serial.print(" - ");
  Serial.print(z);
  Serial.print(" = ");
  Serial.println(x - z);
  //  do it the easy way
  Serial.print("ms.now(): \t");
  Serial.println(y);
  Serial.print(" fib(91): \t");
  Serial.println(print64(big));

  Serial.println("\nDone...");
}


void loop()
{
}


uint64_t fibonaci(uint32_t n)
{
  uint64_t p = 0;
  uint64_t q = 1;
  uint64_t t;
  if (n == 0) return 0;
  if (n == 1) return 1;
  for (uint32_t i = 0; i < n; i++)
  {
    t = p;
    p = q;
    q += t;
    //    Serial.print(i);
    //    Serial.print("\t");
    //    Serial.println(print64(q));
  }
  return q;
}


//  -- END OF FILE --
