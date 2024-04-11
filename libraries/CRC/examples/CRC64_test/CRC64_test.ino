//
//    FILE: CRC64_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC64.h"
#include "printHelpers.h"     //  https://github.com/RobTillaart/printHelpers

char str[24] =  "123456789";


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
  CRC64 crc;
  crc.add((uint8_t*)str, 9);
  Serial.println(print64(crc.calc(), HEX));

  crc.restart();
  for (int i = 0; i < 9; i++)
  {
    crc.add(str[i]);
  }
  Serial.println(print64(crc.calc(), HEX));

  CRC64 customCrc(0x07);
  customCrc.add((uint8_t*)str, 9);
  Serial.println(print64(customCrc.calc(), HEX));

  customCrc.restart();
  for (int i = 0; i < 9; i++)
  {
    customCrc.add(str[i]);
  }
  Serial.println(print64(customCrc.calc(), HEX));
  Serial.println(customCrc.count());
}


//  -- END OF FILE --

