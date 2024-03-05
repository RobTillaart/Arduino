//
//    FILE: MCP23017_digitalWrite.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23017 library
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include "MCP23017.h"


MCP23017 MCP(0x27);


void setup()
{
  Serial.begin(230400);
  Serial.println(__FILE__);
  Serial.print("MCP23017_LIB_VERSION: ");
  Serial.println(MCP23017_LIB_VERSION);

  Wire.begin();

  MCP.begin();

  MCP.pinMode8(0, 0x00);  //  0 = output , 1 = input
  MCP.pinMode8(1, 0x00);
  Wire.setClock(50);

  Serial.println("TEST write1(0)");
  for (int i = 0; i < 16; i++)
  {
    MCP.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST write1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    MCP.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

