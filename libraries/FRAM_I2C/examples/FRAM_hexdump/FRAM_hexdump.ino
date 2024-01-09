//
//    FILE: FRAM_hexdump.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HEX dump FRAM for debugging
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"

FRAM fram;

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

  for (uint32_t addr = 0; addr < 1024; addr += 16)
  {
    //  VERTICAL SEPARATOR
    if (addr % 320 == 0) Serial.println();
    //  ADDRESS
    Serial.println();
    Serial.print(addr);
    Serial.print("\t");
    //  HEX
    for (uint32_t i = 0; i < 16; i++)
    {
      uint8_t b = fram.read8(addr + i);
      if (b < 16) Serial.print(0);
      Serial.print(b, HEX);
      Serial.print("  ");
    }
    Serial.print("  ");
    //  ASCII
    for (uint32_t i = 0; i < 16; i++)
    {
      uint8_t b = fram.read8(addr + i);
      if (isprint(b)) Serial.print((char)b);
      else Serial.print(".");
    }
  }
  Serial.println("\n\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
