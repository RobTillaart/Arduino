//
//    FILE: mcp4725_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Minimal sketch MCP4725 (#29)
//     URL: https://github.com/RobTillaart/MCP4725


#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();

  MCP.begin();
  MCP.setValue(1000);
  
  //  define button
  pinMode(7, INPUT_PULLUP);  //  connect button to GND
}


void loop()
{
  if (digitalRead(7) == LOW)
  {
    MCP.setValue(0);
  }
}


//  -- END OF FILE --

