//
//    FILE: CRC8_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-20
//    (c) : MIT


#include "CRC8.h"

#include "CRC.h"


char str[24] =  "123456789";

CRC8 crc;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // Serial.println("Verified with - https://crccalc.com/\n");

  test();
}


void loop()
{
}

void test()
{
  Serial.println(crc8((uint8_t *)str, 9, 0x07), HEX);

  crc.setPolynome(0x07);
  crc.add((uint8_t*)str, 9);
  Serial.println(crc.getCRC(), HEX);

  crc.reset();
  crc.setPolynome(0x07);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(crc.getCRC(), HEX);

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(crc.getCRC(), HEX);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(crc.getCRC(), HEX);
  Serial.println(crc.count());
}

// -- END OF FILE --
