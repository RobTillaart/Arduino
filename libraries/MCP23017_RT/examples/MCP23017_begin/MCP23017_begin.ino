//
//    FILE: MCP23017_begin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23017 library
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include "MCP23017.h"


MCP23017 MCP(0x38);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23017_LIB_VERSION: ");
  Serial.println(MCP23017_LIB_VERSION);

  Wire.begin();

  //  use default INPUT PULLUP
  bool b = MCP.begin();
  Serial.println(b);
  MCP.pinMode8(0, 0x00);
  MCP.pinMode8(1, 0x00);

  Serial.println("TEST - default INPUT PULLUP");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();


  //  do not set INPUT PULLUP
  b = MCP.begin(false);
  Serial.println(b);
  MCP.pinMode8(0, 0x00);
  MCP.pinMode8(1, 0x00);

  Serial.println("TEST - no INPUT PULLUP");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
