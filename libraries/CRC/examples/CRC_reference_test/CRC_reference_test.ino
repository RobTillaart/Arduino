//
//    FILE: CRC_reference_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC.h"
#include "printHelpers.h"  // for the 64 bit...

char str[24] =  "123456789";


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  uint8_t * data = (uint8_t *) &str[0];

  Serial.println("Verified with - https://crccalc.com/ \n");


  Serial.print("TEST:\t");
  Serial.println(str);
  Serial.println("\nCRC8\n--------------------");
  Serial.println(calcCRC8(data, 9, 0x07), HEX);
  Serial.println(calcCRC8(data, 9, 0x9B, 0xFF), HEX);
  Serial.println(calcCRC8(data, 9, 0x39, 0x00, 0x00, true, true), HEX);
  Serial.println(calcCRC8(data, 9, 0xD5), HEX);
  Serial.println(calcCRC8(data, 9, 0x1D, 0xFF, 0x00, true, true), HEX);
  Serial.println(calcCRC8(data, 9, 0x1D, 0xFD), HEX);
  Serial.println(calcCRC8(data, 9, 0x07, 0x00, 0x55), HEX);
  Serial.println(calcCRC8(data, 9, 0x31, 0x00, 0x00, true, true), HEX);
  Serial.println(calcCRC8(data, 9, 0x07, 0xFF, 0x00, true, true), HEX);
  Serial.println(calcCRC8(data, 9, 0x9B, 0x00, 0x00, true, true), HEX);
  Serial.println();


  Serial.println("CRC16\n--------------------");
  Serial.println(calcCRC16(data, 9, 0x1021, 0xFFFF, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0x0000, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0x1D0F, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0x0000, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0xC867, 0xFFFF, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0x800D, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x0589, 0x0000, 0x0001, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x0589, 0x0000, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x3D65, 0x0000, 0xFFFF, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x3D65, 0x0000, 0xFFFF, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0xFFFF, 0xFFFF, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0x0000, 0xFFFF, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0xFFFF, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0xB2AA, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8BB7, 0x0000, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0xA097, 0x0000, 0x0000, false, false ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0x89EC, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0xFFFF, 0xFFFF, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0xC6C6, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0x0000, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x8005, 0xFFFF, 0x0000, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0xFFFF, 0xFFFF, true,  true  ), HEX);
  Serial.println(calcCRC16(data, 9, 0x1021, 0x0000, 0x0000, false, false ), HEX);
  Serial.println();


  Serial.println("CRC32\n--------------------");
  Serial.println(calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true), HEX);
  Serial.println(calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false), HEX);
  Serial.println(calcCRC32(data, 9, 0x1EDC6F41, 0xFFFFFFFF, 0xFFFFFFFF, true, true), HEX);
  Serial.println(calcCRC32(data, 9, 0xA833982B, 0xFFFFFFFF, 0xFFFFFFFF, true, true), HEX);
  Serial.println(calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, false, false), HEX);
  Serial.println(calcCRC32(data, 9, 0x04C11DB7, 0x00000000, 0xFFFFFFFF, false, false), HEX);
  Serial.println(calcCRC32(data, 9, 0x814141AB, 0x00000000, 0x00000000, false, false), HEX);
  Serial.println(calcCRC32(data, 9, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true), HEX);
  Serial.println(calcCRC32(data, 9, 0x000000AF, 0x00000000, 0x00000000, false, false), HEX);
  Serial.println();


  Serial.println("\nCRC64 - no reference\n--------------------");
  uint64_t t = calcCRC64(data, 9, 0x814141AB, 0x00000000, 0x00000000, false, false);
  Serial.println(print64(t, HEX));


  Serial.println("\n\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

