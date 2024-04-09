//
//    FILE: bitHelpers_demo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/bitHelpers


#include "bitHelpers.h"
#include "printHelpers.h"

uint32_t start, stop, d1, d2;
uint64_t x = 0;


void setup()
{
  Serial.begin(115200);

  Serial.println("BITSET");
  start = micros();
  for (int i = 0; i < 64; i++) mbitSet64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);
  start = micros();
  for (int i = 0; i < 64; i++) bitSet64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);

  Serial.println("BITCLEAR");
  start = micros();
  for (int i = 0; i < 64; i++) mbitClear64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);
  start = micros();
  for (int i = 0; i < 64; i++) bitClear64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);

  Serial.println("BITTOGGLE");
  start = micros();
  for (int i = 0; i < 64; i++) mbitToggle64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);
  start = micros();
  for (int i = 0; i < 64; i++) bitToggle64(x, i);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);

  Serial.println("BITS NEEDED");
  x = (1ULL << 63);
  Serial.println(bitsNeededRef(x));
  Serial.println(bitsNeeded(x));
  start = micros();
  for (int i = 0; i < 64; i++) bitsNeededRef(x);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);
  start = micros();
  for (int i = 0; i < 64; i++) bitsNeeded(x);
  d1 = micros() - start;
  Serial.println(d1 / 64.0);
  delay(10);

  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

