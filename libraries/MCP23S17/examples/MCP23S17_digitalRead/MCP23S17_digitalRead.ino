//
//    FILE: MCP23S17_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23S17 library
//     URL: https://github.com/RobTillaart/MCP23S17


#include "MCP23S17.h"


MCP23S17 MCP(10);
int rv = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_VERSION: ");
  Serial.println(MCP23S17_LIB_VERSION);
  delay(100);

  SPI.begin();

  rv = MCP.begin();
  Serial.println(rv ? "true" : "false");

  rv = MCP.pinMode8(0, 0xFF);
  Serial.println(rv);
  rv = MCP.pinMode8(1, 0xFF);
  Serial.println(rv);


  Serial.print("HWSPI: ");
  Serial.println(MCP.usesHWSPI());

  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
}


void loop()
{
  delay(1000);
  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();

}


//  -- END OF FILE --

