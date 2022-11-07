//
//    FILE: Fletcher_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher16.h"
#include "Fletcher32.h"
#include "Fletcher64.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers


Fletcher16 F16;
Fletcher32 F32;
Fletcher64 F64;

uint32_t count = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  F16.begin();
  F32.begin();
  F64.begin();
}


void loop()
{
  uint32_t r32 = random(0x7FFFFFFF) * random(0x7FFFFFFF) + random(0x7FFFFFFF);
  uint16_t r16 = r32 & 0xFFFF;
  uint8_t r8 = r16 & 0xFF;

  uint16_t x16 = F16.getFletcher();
  F16.add(r8);
  if (F16.getFletcher() != ref16(r8))
  {
    Serial.print("16:\t");
    Serial.print(x16);
    Serial.print(" + ");
    Serial.print(r8);
    Serial.print("==>");
    Serial.print(F16.getFletcher());
    Serial.println();
    while (1);
  }

  uint32_t x32 = F32.getFletcher();
  F32.add(r16);
  if (F32.getFletcher() != ref32(r16))
  {
    Serial.print("32:\t");
    Serial.print(x32);
    Serial.print(" + ");
    Serial.print(r16);
    Serial.print("==>");
    Serial.print(F32.getFletcher());
    Serial.println();
    while (1);
  }

  uint64_t x64 = F64.getFletcher();
  F64.add(r32);
  if (F64.getFletcher() != ref64(r32))
  {
    Serial.print("64:\t");
    Serial.print(print64(x64));
    Serial.print(" + ");
    Serial.print(r32);
    Serial.print("==>");
    Serial.print(print64(F64.getFletcher()));
    Serial.println();
    while (1);
  }

  count++;
  if (count % 100000 == 0)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(count);
    Serial.print("\t");
    Serial.println(count * 1000.0 / millis());
  }
}

uint64_t ref64(uint32_t x)
{
  static uint64_t s1 = 0;
  static uint64_t s2 = 0;

  s1 += x;
  s1 %= 0xFFFFFFFF;
  s2 += s1;
  s2 %= 0xFFFFFFFF;
  return (s2 << 32 | s1);
}


uint32_t ref32(uint16_t x)
{
  static uint32_t s1 = 0;
  static uint32_t s2 = 0;

  s1 += x;
  s1 %= 0xFFFF;
  s2 += s1;
  s2 %= 0xFFFF;
  return (s2 << 16 | s1);
}


uint16_t ref16(uint8_t x)
{
  static uint16_t s1 = 0;
  static uint16_t s2 = 0;

  s1 += x;
  s1 %= 0xFF;
  s2 += s1;
  s2 %= 0xFF;
  return (s2 << 8 | s1);
}


// -- END OF FILE --
