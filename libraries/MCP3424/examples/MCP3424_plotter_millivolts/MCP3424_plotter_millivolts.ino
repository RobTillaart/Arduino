//
//    FILE: MCP3424_plotter_millivolts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple plotter
//     URL: https://github.com/RobTillaart/MCP3424
//
//  use for Arduino plotter

#include "MCP3424.h"

MCP3424 mcp;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("MCP3424_LIB_VERSION: ");
  //  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  if (mcp.begin() == false)
  {
    Serial.println("Could not connect...");
    while (1);
  }

  //  sample frequency is resolution dependent.
  mcp.setResolution(16);
  mcp.setGain(1);

  Serial.println("CH01, CH02, CH03, CH04");
}


void loop()
{
  for (int channel = 0; channel < 4; channel++)
  {
    mcp.setChannel(channel);
    Serial.println(mcp.readMilliVolts(), 3);
    delay(mcp.getConversionDelay());  //  blocking
  }
}


//  -- END OF FILE --
