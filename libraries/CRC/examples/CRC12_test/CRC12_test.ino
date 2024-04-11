//
//    FILE: CRC16_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC12.h"
#include "CRC.h"


char str1[24] =  "123456789";
char str2[24] =  "123456789123456789";

CRC12 crc;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  //  Serial.println("Verified with - http://zorc.breitbandkatze.de/crc.html \n");

  test();
}


void loop()
{
}


void test()
{
  //  calcCRCxx() uses default parameters
  Serial.println(crc_check((uint8_t *) str1, 9), HEX);
  Serial.println(calcCRC12((uint8_t *) str1, 9), HEX);
  Serial.println(crc_check((uint8_t *) str2, 18), HEX);
  Serial.println(calcCRC12((uint8_t *) str2, 18), HEX);

  crc.add((uint8_t*)str1, 9);
  Serial.println(crc.calc(), HEX);
  crc.add((uint8_t*)str2, 9);
  Serial.println(crc.calc(), HEX);

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str1[i]);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(crc.calc(), HEX);
  }
  Serial.println(crc.count());
}


//  reference function

uint16_t crc_check(uint8_t * ptr, uint8_t length)   //  crc12
{
  uint16_t crc12out = 0;
  uint8_t i, j;
  for (j = 0; j < length; j++)
  {
    for (i = 0; i < 8; i++)
    {
      if (*(ptr + j) & (0x80 >> i)) crc12out |= 0x01;
      if (crc12out >= 0x1000) crc12out ^= 0x180D;
      crc12out <<= 1;
    }
  }
  for (i = 0; i < 12; i ++)
  {
    if (crc12out >= 0x1000) crc12out ^= 0x180D;
    crc12out <<= 1;
  }
  crc12out >>= 1;
  return crc12out;
}


//  -- END OF FILE --
