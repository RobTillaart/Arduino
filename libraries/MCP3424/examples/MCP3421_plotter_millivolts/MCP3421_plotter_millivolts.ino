//
//    FILE: MCP3421_plotter_millivolts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple plotter
//     URL: https://github.com/RobTillaart/MCP3424
//
//  use for Arduino plotter

#include "MCP3424.h"

MCP3421 mcp;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  // Serial.println();
  // Serial.println(__FILE__);
  // Serial.print("MCP3424_LIB_VERSION: ");
  // Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  if (mcp.begin() == false)
  {
    Serial.println("Could not connect...");
    while (1);
  }

  mcp.setResolution(18);
  mcp.setGain(1);

  Serial.println("milliVolts, ");
}


void loop()
{
  Serial.println(mcp.readMilliVolts(), 3);
  delay(50);
}


//  -- END OF FILE --
