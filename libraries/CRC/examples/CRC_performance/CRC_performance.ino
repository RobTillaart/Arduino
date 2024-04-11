//
//    FILE: CRC_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC.h"

char str[122] =  "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  uint8_t * data = (uint8_t *) &str[0];
  uint8_t len = strlen(str);

  Serial.println("Calculating CRC of 100 bytes message\n");
  delay(100);

  start = micros();
  uint8_t x8 = calcCRC8(data, len, 0x07, 0x00, 0x00, false, false);
  stop = micros();
  Serial.print("CRC8:\t");
  Serial.println(x8, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x8 = calcCRC8(data, len, 0x07, 0x00, 0x00, true, true);
  stop = micros();
  Serial.print("CRC8:\t");
  Serial.println(x8, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println("=============================");
  delay(100);


  start = micros();
  uint16_t x16 = calcCRC16(data, len, 0x1021, 0xFFFF, 0x0000, false, false);
  stop = micros();
  Serial.print("CRC16:\t");
  Serial.println(x16, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x16 = calcCRC16(data, len, 0x1021, 0xFFFF, 0x0000, true, true);
  stop = micros();
  Serial.print("CRC16:\t");
  Serial.println(x16, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println("=============================");
  delay(100);


  start = micros();
  uint32_t x32 = calcCRC32(data, len, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, false, false);
  stop = micros();
  Serial.print("CRC32:\t");
  Serial.println(x32, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x32 = calcCRC32(data, len, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
  stop = micros();
  Serial.print("CRC32:\t");
  Serial.println(x32, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println("=============================");
  delay(100);

  start = micros();
  uint64_t x64 = calcCRC64(data, len, 0x814141AB, 0x00000000, 0x00000000, false, false);
  stop = micros();
  Serial.print("CRC64:\t");
  Serial.print((uint32_t)(x64 >> 32), HEX);
  Serial.println((uint32_t)(x64 & 0xFFFFFFFF), HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x64 = calcCRC64(data, len, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
  stop = micros();
  Serial.print("CRC64:\t");
  Serial.print((uint32_t)(x64 >> 32), HEX);
  Serial.println((uint32_t)(x64 & 0xFFFFFFFF), HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println("=============================");
  delay(100);

  Serial.println("\n\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

