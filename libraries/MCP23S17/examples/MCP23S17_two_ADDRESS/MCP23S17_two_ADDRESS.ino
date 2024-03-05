//
//    FILE: MCP23S17_two_ADDRESS.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two MCP23S17 devices
//     URL: https://github.com/RobTillaart/MCP23S17
//
// #19, experimental, not tested wirth hardware yet


#include "MCP23S17.h"


//MCP23S17 MCP_A(10, 12, 11, 13, 0);   //  SW SPI, address 0
//MCP23S17 MCP_B(10, 12, 11, 13, 1);   //  SW SPI, address 1

MCP23S17 MCP_A(10, &SPI);   //  HW SPI, address 0 (default)
MCP23S17 MCP_B(10, 1);      //  HW SPI, address 1


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();

  MCP_A.begin();
  MCP_B.begin();
  MCP_A.enableHardwareAddress();
  MCP_B.enableHardwareAddress();

  //  test connected
  int c = testConnection(MCP_A);
  Serial.print("Connect A: ");
  Serial.println(c);
  c = testConnection(MCP_B);
  Serial.print("Connect B: ");
  Serial.println(c);

  //  all pins OUTPUT  LOW
  MCP_A.pinMode16(0);
  MCP_A.write16(0x0000);
  MCP_B.pinMode16(0);
  MCP_B.write16(0x0000);
}


void loop()
{
  int x = random(32);
  Serial.println(x);
  if (x < 16)
  {
    MCP_A.write1(x, HIGH);
    delay(100);
    MCP_A.write1(x, LOW);
  }
  else
  {
    x -= 16;
    MCP_B.write1(x, HIGH);
    delay(100);
    MCP_B.write1(x, LOW);
  }
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
