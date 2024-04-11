//
//    FILE: CRC8_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC8.h"

byte arr[7] = { 0x13, 0x54, 0x13, 0x88, 0x00, 0x0e, 0x99 };

CRC8 crc(0x1D, 0xFF, 0xFF, false, false);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  crc.add((uint8_t*)arr, 7);
  Serial.println(crc.calc(), HEX);

  crc.restart();
  for (int i = 0; i < 7; i++)
  {
    crc.add(arr[i]);
  }
  uint8_t result = crc.calc();
  Serial.println(result, HEX);
  Serial.println(crc.count());
}

void loop()
{
}

//  -- END OF FILE --
