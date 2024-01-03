//
//    FILE: bcd_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: bcd test
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
volatile uint8_t z;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(100);

  Serial.print("dec2bcdRef:\t");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcdRef(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);


  Serial.print("dec2bcd:\t");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcd(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);


  Serial.print("dec2bcdRTC:\t");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcdRTC(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  //  not 100% correct but it measures performance
  Serial.print("bcd2decRef:\t");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = bcd2decRef(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  //  not 100% correct but it measures performance
  Serial.print("bcd2dec:\t");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = bcd2dec(x);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  Serial.println();
  Serial.println("compare bcd2dec <-> dec2bcd (0..100)");
  delay(10);
  start = micros();
  for (uint8_t x = 0; x < 100; x++)
  {
    z = dec2bcd(x);
    if (x != bcd2dec(z))
    {
      Serial.print(".");
    }
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);


  Serial.println("compare bcd2dec <-> dec2bcdRTC (0..60)");
  start = micros();
  for (uint8_t x = 0; x < 60; x++)
  {
    z = dec2bcdRTC(x);
    if (x != bcd2dec(z))
    {
      Serial.print(z, HEX);
      Serial.print(" ");
      Serial.print(x);
      Serial.print(" ");
    }
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
