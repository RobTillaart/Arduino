//
//    FILE: MCP23S17_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23S17 library
//     URL: https://github.com/RobTillaart/MCP23S17


#include "MCP23S17.h"


// MCP23S17 MCP(10, 12, 11, 13);  //  SW SPI address 0x00
MCP23S17 MCP(10);           //  HW SPI address 0x00


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();

  bool b = MCP.begin();
  Serial.println(b ? "true" : "false");

  MCP.pinMode8(0, 0x00);  //  0 = output, 1 = input
  MCP.pinMode8(1, 0x00);


  //////////////////////////////////////////////////////////////
  //
  //  test 8 bit interface
  //
  Serial.println("TEST digitalWrite8(port, value)");
  for (uint16_t i = 0; i < 256; i++)
  {
    MCP.write8(0, i);
    MCP.write8(1, i);
    uint8_t mask0 = MCP.read8(0);
    uint8_t mask1 = MCP.read8(1);
    if ((mask0 != i) || (mask1 != i))
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(MCP.read8(0));
      Serial.print("\t");
      Serial.print(MCP.read8(1));
      Serial.println();
    }
  }


  Serial.println("TEST setPullup8(port, value)");
  for (uint16_t i = 0; i < 256; i++)
  {
    MCP.setPullup8(0, i);
    MCP.setPullup8(1, i);
    uint8_t mask0, mask1;
    MCP.getPullup8(0, mask0);
    MCP.getPullup8(1, mask1);
    if ((mask0 != i) || (mask1 != i))
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(mask0);
      Serial.print("\t");
      Serial.print(mask1);
      Serial.println();
    }
  }


  Serial.println("TEST setPolarity8(port, value)");
  for (uint16_t i = 0; i < 256; i++)
  {
    MCP.setPolarity8(0, i);
    MCP.setPolarity8(1, i);
    uint8_t mask0, mask1;
    MCP.getPolarity8(0, mask0);
    MCP.getPolarity8(1, mask1);
    if ((mask0 != i) || (mask1 != i))
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(mask0);
      Serial.print("\t");
      Serial.print(mask1);
      Serial.println();
    }
  }


  //////////////////////////////////////////////////////////////
  //
  //  test 16 bit interface
  //
  Serial.println("TEST digitalWrite16(value)");
  for (uint32_t i = 0; i < 65535; i++)
  {
    MCP.write16(i);
    if (MCP.read16() != i)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(MCP.read16());
      Serial.println();
    }
  }

  Serial.println("TEST setPullup16(value)");
  for (uint32_t i = 0; i < 65535; i++)
  {
    MCP.setPullup16(i);
    uint16_t mask = 0;
    MCP.getPullup16(mask);
    if (mask != i)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(mask);
      Serial.println();
    }
  }

  Serial.println("TEST setPolarity16(value)");
  for (uint32_t i = 0; i < 65535; i++)
  {
    MCP.setPolarity16(i);
    uint16_t mask = 0;
    MCP.getPolarity16(mask);
    if (mask != i)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(mask);
      Serial.println();
    }
  }

}


void loop()
{
}


//  -- END OF FILE --

