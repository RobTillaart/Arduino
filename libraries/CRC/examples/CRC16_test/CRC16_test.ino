//
//    FILE: CRC16_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-20
//    (c) : MIT


#include "CRC16.h"
#include "CRC.h"

char str[24] =  "123456789";

CRC16 crc;


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
  Serial.println(crc16((uint8_t *) str, 9, 0x1021, 0, 0, false, false), HEX);
  
  crc.setPolynome(0x1021);
  crc.add((uint8_t*)str, 9);
  Serial.println(crc.getCRC(), HEX);

  crc.reset();
  crc.setPolynome(0x1021);
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(crc.getCRC(), HEX);
  }

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

