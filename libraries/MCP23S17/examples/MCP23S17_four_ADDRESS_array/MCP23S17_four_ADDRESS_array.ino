//
//    FILE: MCP23S17_four_ADDRESS_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two MCP23S17 devices
//     URL: https://github.com/RobTillaart/MCP23S17
//
// #27, experimental, not tested with hardware yet


#include "MCP23S17.h"


MCP23S17 MCP_A(10, 12, 11, 13, 0);   //  SW SPI, address 0
MCP23S17 MCP_B(10, 12, 11, 13, 1);   //  SW SPI, address 1
MCP23S17 MCP_C(10, 12, 11, 13, 2);   //  SW SPI, address 2
MCP23S17 MCP_D(10, 12, 11, 13, 3);   //  SW SPI, address 3

//  MCP23S17 MCP_A(10, 0);   //  HW SPI, address 0
//  MCP23S17 MCP_B(10, 1);   //  HW SPI, address 1
//  MCP23S17 MCP_C(10, 2);   //  HW SPI, address 2
//  MCP23S17 MCP_D(10, 3);   //  HW SPI, address 3

MCP23S17 MCP[4] = { MCP_A, MCP_B, MCP_C, MCP_D };


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();

  for (int addr = 0; addr < 4; addr++)
  {
    MCP[addr].begin();
    MCP[addr].enableHardwareAddress();
  }

  //  test connected
  for (int addr = 0; addr < 4; addr++)
  {
    Serial.print(addr);
    Serial.print("\t");
    Serial.println(testConnection(MCP[addr]));
  }

  //  set all pins OUTPUT => LOW
  for (int addr = 0; addr < 4; addr++)
  {
    MCP[addr].pinMode16(0);
    MCP[addr].write16(0x0000);
  }
}


void loop()
{
  int pin  = random(64);
  int addr = random(4);
  MCP[addr].write1(pin, HIGH);
  delay(100);
  MCP[addr].write1(pin, LOW);
  delay(100);
}



//
//  the connection test tries to write a magic number to a register
//  and read it back. If it is the same it is assumed to be connected
//
int testConnection(MCP23S17 & mcp)
{
  uint16_t magic_test_number = 0xABCD;

  //  Read the current polarity config to restore later
  uint16_t old_value;
  if (! mcp.getPolarity16(old_value)) return -1;

  //  Write the magic number to polarity register
  if (! mcp.setPolarity16(magic_test_number)) return -2;

  //  Read back the magic number from polarity register
  uint16_t temp;
  if (! mcp.getPolarity16(temp)) return -3;

  //  Write old config to polarity register
  if (! mcp.setPolarity16(old_value)) return -4;

  //  Check the magic connection test
  if (temp != magic_test_number) return -5;

  return 0;  //  OK
}

//  -- END OF FILE --
