//
//    FILE: SHT2x_test_CRC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

uint32_t start, stop;

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

//  uint8_t buf[3] = { 0x7C, 0x82, 0 };
//  Serial.println(sht.crc8(buf, 2), HEX);  // 97
//  uint8_t buf[3] = { 0x68, 0x3A, 0 };
//  Serial.println(sht.crc8(buf, 2), HEX);  // 7C
  uint8_t buf[3] = { 0x4E, 0x85, 0 };
  Serial.println(sht.crc8(buf, 2), HEX);   // 6B
}


void loop()
{

}


//  -- END OF FILE --
