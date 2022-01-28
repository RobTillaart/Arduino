//
//    FILE: CRC64_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-20
//    (c) : MIT


#include "CRC64.h"
#include "printHelpers.h"     // https://github.com/RobTillaart/printHelpers

char str[24] =  "123456789";

CRC64 crc;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // Serial.println("Verified with - http://zorc.breitbandkatze.de/crc.html \n");

  test();
}


void loop()
{
}


void test()
{
  crc.setPolynome(0x07);
  crc.add((uint8_t*)str, 9);
  Serial.println(print64(crc.getCRC(), HEX));

  crc.reset();
  crc.setPolynome(0x07);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(print64(crc.getCRC(), HEX));

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(print64(crc.getCRC(), HEX));
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(print64(crc.getCRC(), HEX));
  Serial.println(print64(crc.count()));
}


// -- END OF FILE --

