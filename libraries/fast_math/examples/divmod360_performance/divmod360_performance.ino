//
//    FILE: divmod360_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: divmod360 performance test
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
volatile uint32_t x;
uint32_t d;
uint16_t m;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(1000);

  x = random(4000000000ULL);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    d = x / 360;
    m = x % 360;
  }
  stop = micros();
  Serial.print("div + mod: ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(d);
  Serial.print("\t");
  Serial.print(m);
  Serial.print("\n");
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    divmod360(x, &d, &m);
  }
  stop = micros();
  Serial.print("divmod360:  ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(d);
  Serial.print("\t");
  Serial.print(m);
  Serial.print("\n");
  delay(100);

  Serial.println("\nTest 0 .. 1 million (2 minute UNO, < 2 second ESP32)");
  start = micros();
  for (uint32_t x = 0; x <= 1000000; x++)
  {
    if (x % 100000 == 0) Serial.println(x);
    divmod360(x, &d, &m);
    if (x != (d * 360 + m))
    {
      Serial.print(x);
      Serial.print("\t");
      Serial.print(d);
      Serial.print("\t");
      Serial.print(m);
      Serial.print("\n");
    }
  }
  stop = micros();
  Serial.print((stop - start) * 1e-6);
  Serial.print("\n");

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
