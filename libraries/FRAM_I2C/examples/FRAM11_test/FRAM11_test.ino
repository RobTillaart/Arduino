//
//    FILE: FRAM11_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo FRAM11 memory test
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"

FRAM11 fram;

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

  //  get size
  Serial.print("   KB  :\t");
  Serial.println(fram.getSize());
  Serial.print("BYTES  :\t");
  Serial.println(fram.getSizeBytes());
  sizeInBytes = fram.getSizeBytes();

  delay(100);

  test();

  Serial.println("done...");
}


void loop()
{
}


void test()
{
  //  addr goes from 0 .. 2047
  //  value goes from 0.. 255

  uint8_t value = 0x00;
  for (uint32_t addr = 0; addr < sizeInBytes; addr++)
  {
    if (addr % 8 == 0) value++;
    fram.write8(addr, value);
    Serial.print("Write\t");
    Serial.print(addr);
    Serial.print("\t");
    Serial.println(value);
  }

  // read back
  value = 0x00;
  for (uint32_t addr = 0; addr < sizeInBytes; addr++)
  {
    if (addr % 8 == 0) value++;
    uint8_t x = fram.read8(addr);
    if (x != value)
    {
      Serial.print("Read\t");
      Serial.print(addr);
      Serial.print("\t");
      Serial.println(value);
    }
  }

}

//  -- END OF FILE --
