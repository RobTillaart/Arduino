//
//    FILE: MCP23S17_test_connection.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23S17 library
//     URL: https://github.com/RobTillaart/MCP23S17
//
// see issue #13 library


#include "MCP23S17.h"


// MCP23S17 MCP(10, 12, 11, 13);  //  SW SPI address 0x00
MCP23S17 MCP(10, 4);           //  HW SPI address 4


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();

  MCP.begin();

  int c = testConnection(MCP);
  Serial.print("connection: ");
  Serial.println(c);
}


void loop()
{
}


int testConnection(MCP23S17 & mcp)
{
  uint16_t magic_test_number = 0xABCD;

  //  Read the current polarity configuration to restore later
  uint16_t old_value;
  if (! mcp.getPolarity16(old_value)) return -1;

  //  Write the magic number to polarity register
  if (! mcp.setPolarity16(magic_test_number)) return -2;

  //  Read back the magic number from polarity register
  uint16_t temp;
  if (! mcp.getPolarity16(temp)) return -3;

  //  Write old configuration to polarity register
  if (! mcp.setPolarity16(old_value)) return -4;

  //  Check the magic connection test
  if (temp != magic_test_number) return -5;

  return 0;  //  OK
}


//  -- END OF FILE --
