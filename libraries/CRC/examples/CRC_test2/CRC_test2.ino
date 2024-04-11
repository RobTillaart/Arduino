//
//    FILE: CRC_test2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC.h"
#include "printHelpers.h"  //  for the 64 bit...

char str[24] =  "123456789";


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  uint8_t * data = (uint8_t *) &str[0];

  Serial.println("Verified with - https://crccalc.com/ \n");

  Serial.print("TEST:\t");
  Serial.println(str);
  Serial.print("CRC8:\t");
  Serial.println(crc8(data, 9, 0x07, 0x00, 0x00, false, false), HEX);
  Serial.print("CRC16:\t");
  Serial.println(crc16(data, 9, 0x1021, 0x0000, 0x0000, false, false ), HEX);
  Serial.print("CRC32:\t");
  Serial.println(crc32(data, 9, 0x04C11DB7, 0x00000000, 0x00000000, false, false), HEX);
//  Serial.print("*CRC64:\t");
//  uint64_t t = crc64(data, 9, 0x814141AB, 0x00000000, 0x00000000, false, false);
//  Serial.println(print64(t, HEX));
  
  Serial.println("\n\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
