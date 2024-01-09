//
//    FILE: FRAM32_clear.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo clear FRAM
//     URL: https://github.com/RobTillaart/FRAM_I2C
//
//  performance test "clear" function.


#include "FRAM.h"

FRAM32 fram;

uint32_t start;
uint32_t stop;

uint32_t sizeInBytes = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  //  get size in bytes
  sizeInBytes = fram.getSize() * 1024;
  Serial.print("BYTES  :\t");
  Serial.println(sizeInBytes);
  delay(100);

  Serial.println("\nSPEED  :\t100000");
  Wire.setClock(100000);
  test();

  Serial.println("\nSPEED  :\t200000");
  Wire.setClock(200000);
  test();

  Serial.println("\nSPEED  :\t400000");
  Wire.setClock(400000);
  test();
  
  Serial.println("\nSPEED  :\t800000");
  Wire.setClock(800000);
  test();


  Serial.println("done...");
}


void loop()
{
}


void test()
{
  start = micros();
  for (uint32_t addr = 0; addr < sizeInBytes; addr++)
  {
    fram.write8(addr, 0x00);
  }
  stop = micros();
  Serial.print("BYTES 1:\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);


  start = micros();
  for (uint32_t addr = 0; addr < sizeInBytes; addr += 2)
  {
    fram.write16(addr, 0x0000);
  }
  stop = micros();
  Serial.print("BYTES 2:\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);


  start = micros();
  for (uint32_t addr = 0; addr < sizeInBytes; addr += 4)
  {
    fram.write32(addr, 0x00000000);
  }
  stop = micros();
  Serial.print("BYTES 4:\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);


  uint8_t buf[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  start = micros();
  for (uint32_t addr = 0; addr < sizeInBytes; addr += 8)
  {
    fram.write(addr, buf, 8);
  }
  stop = micros();
  Serial.print("BYTES 8:\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);


  start = micros();
  for (uint32_t addr = 0; addr < sizeInBytes; addr += 16)
  {
    fram.write(addr, buf, 16);
  }
  stop = micros();
  Serial.print("BYTES 16:\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);


  start = micros();
  fram.clear();
  stop = micros();
  Serial.print("CLEAR():\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);

  
  start = micros();
  fram.clear(0xFF);
  stop = micros();
  Serial.print("CLEAR(0xFF):\t");
  Serial.print(stop - start);
  Serial.print(" ==> \t");
  Serial.print((stop - start) * 1.0 / 32768.0);
  Serial.println(" us/byte");
  delay(100);
}

//  -- END OF FILE --
