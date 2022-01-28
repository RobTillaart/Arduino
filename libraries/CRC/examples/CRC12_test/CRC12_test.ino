//
//    FILE: CRC16_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-01-24
//    (c) : MIT


#include "CRC12.h"
#include "CRC.h"

char str1[24] =  "123456789";
char str2[24] =  "123456789123456789";

CRC12 crc;


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
  Serial.println(crc_check((uint8_t *) str1, 9), HEX);
  Serial.println(crc12((uint8_t *) str1, 9, 0x180D, 0, 0, false, false), HEX);
  Serial.println(crc_check((uint8_t *) str2, 18), HEX);
  Serial.println(crc12((uint8_t *) str2, 18, 0x180D, 0, 0, false, false), HEX);

  crc.setPolynome(0x080D);
  crc.add((uint8_t*)str1, 9);
  Serial.println(crc.getCRC(), HEX);
  crc.reset();
  crc.setPolynome(0x080D);
  crc.add((uint8_t*)str2, 18);
  Serial.println(crc.getCRC(), HEX);


  crc.reset();
  crc.setPolynome(0x180D);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str1[i]);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(crc.getCRC(), HEX);
  }

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str1[i]);
  }
  Serial.println(crc.getCRC(), HEX);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str1[i]);
  }
  Serial.println(crc.getCRC(), HEX);
  Serial.println(crc.count());
}

////
// reference function

uint16_t crc_check(uint8_t * ptr, uint8_t length)   // crc12
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




// -- END OF FILE --
