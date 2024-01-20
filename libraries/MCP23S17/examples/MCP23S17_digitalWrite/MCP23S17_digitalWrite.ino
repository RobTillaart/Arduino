//
//    FILE: MCP23S17_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23S17 library
//     URL: https://github.com/RobTillaart/MCP23S17


#include "MCP23S17.h"


MCP23S17 MCP(10, 5, 6, 7);   //  SW SPI   address 0x00


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  delay(100);

  SPI.begin();

  bool b = MCP.begin();
  Serial.println(b ? "true" : "false");
  delay(100);

  MCP.pinMode8(0, 0x00);  //  0 = output , 1 = input
  MCP.pinMode8(1, 0x00);

  Serial.println("TEST write1(0)");
  delay(100);
  for (int i = 0; i < 16; i++)
  {
    MCP.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST write1(pin)");
  delay(100);
  for (int pin = 0; pin < 16; pin++)
  {
    MCP.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

