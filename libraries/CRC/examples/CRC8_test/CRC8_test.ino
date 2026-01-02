//
//    FILE: CRC8_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC8.h"
#include "CRC.h"


char str[24] =  "123456789";

CRC8 crc(0x31, 0xFF);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("CRC_LIB_VERSION: ");
  Serial.println(CRC_LIB_VERSION);
  Serial.println();

  //  Serial.println("Verified with - http://zorc.breitbandkatze.de/crc.html \n");

  test();
}


void loop()
{
}


void test()
{
  Serial.println(calcCRC8((uint8_t *)str, 9), HEX);

  crc.add((uint8_t*)str, 9);
  Serial.println(crc.calc(), HEX);

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(crc.calc(), HEX);
  Serial.println(crc.count());
}


//  -- END OF FILE --
