//
//    FILE: MCP23017_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo array of multiple MCP23017
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include "MCP23017.h"


//  adjust addresses to your needs
//  optional add WIRE bus in constructors.
MCP23017 MCParray[4] = {
  MCP23017(0x27),
  MCP23017(0x28),
  MCP23017(0x29),
  MCP23017(0x2A)
};



void setup()
{
  Serial.begin(230400);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP23017_LIB_VERSION: ");
  Serial.println(MCP23017_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();

  for (int device = 0; device < 4; device++)
  {
    bool b = MCParray[device].begin();
    Serial.print(device);
    Serial.println(b ? " => true" : "  => false");
  }

  //  set all pins to output
  for (int device = 0; device < 4; device++)
  {
    //  0 = output , 1 = input
    MCParray[device].pinMode16(0x0000);  
    MCParray[device].write16(0x0000);  
  }

}


void loop()
{
  //  now we have 64 output pins.
  for (int i = 0; i < 64; i++)
  {
    int device = i / 4;
    int pin    = i % 16;
    MCParray[device].write1(pin, 1);
    delay(100);
    MCParray[device].write1(pin, 0);
  }
}


//  -- END OF FILE --
