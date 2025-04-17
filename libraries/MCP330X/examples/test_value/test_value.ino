//    FILE: test_value.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2025-04-16
// PURPOSE: test return value MCP330X
//     URL: https://github.com/RobTillaart/MCP330X

#include "Arduino.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  //  table 6.1 page 23
  Serial.println(construct(0x0F, 0xFF));
  Serial.println(construct(0x0F, 0xFE));
  Serial.println(construct(0x00, 0x02));
  Serial.println(construct(0x00, 0x01));
  Serial.println(construct(0x1F, 0xFF));
  Serial.println(construct(0x1F, 0xFE));
  Serial.println(construct(0x10, 0x02));
  Serial.println(construct(0x10, 0x01));
  Serial.println(construct(0x10, 0x00));
}

void loop()
{
}

int16_t construct(uint8_t a, uint8_t b)
{
  int16_t raw = 256 * a + b;
  raw &= 0x1FFF;      //  clear all unknown bits.
  if (raw & 0x1000)   //  sign bit set?
  {
    // extend sign bits
    raw |= 0xF000;    //  absolute value
    return raw;
  }
  //  positive value
  return raw;
}

// -- END OF FILE --
