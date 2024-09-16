//
//    FILE: MCP3424_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: basic test API calls.
//     URL: https://github.com/RobTillaart/MCP3424


#include "MCP3424.h"


MCP3424 mcp;



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP3424_LIB_VERSION: ");
  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  mcp.begin();

  Serial.println();
  Serial.print("Address:\t");
  Serial.println(mcp.getAddress(), HEX);
  Serial.print("Connect:\t");
  Serial.println(mcp.isConnected());
  Serial.print("Channels:\t");
  Serial.println(mcp.getMaxChannels());
  Serial.print("Gain:\t");
  Serial.println(mcp.getGain());
  Serial.print("Bits:\t");
  Serial.println(mcp.getResolution());
  Serial.println();

  Serial.println("GAIN 1");
  mcp.setGain(1);
  Serial.println(mcp.read());
  Serial.println(mcp.readVolts(), 6);
  Serial.println(mcp.readMilliVolts(), 3);
  Serial.println(mcp.readMicroVolts(), 3); 
  Serial.println(); 

  Serial.println("GAIN 2");
  mcp.setGain(2);
  Serial.println(mcp.read());
  Serial.println(mcp.readVolts(), 6);
  Serial.println(mcp.readMilliVolts(), 3);
  Serial.println(mcp.readMicroVolts(), 3); 
  Serial.println();
  
  Serial.println("GAIN 4");
  mcp.setGain(4);
  Serial.println(mcp.read());
  Serial.println(mcp.readVolts(), 6);
  Serial.println(mcp.readMilliVolts(), 3);
  Serial.println(mcp.readMicroVolts(), 3); 
  Serial.println(); 

  Serial.println("GAIN 8");
  mcp.setGain(8);
  Serial.println(mcp.read());
  Serial.println(mcp.readVolts(), 6);
  Serial.println(mcp.readMilliVolts(), 3);
  Serial.println(mcp.readMicroVolts(), 3); 
  Serial.println(); 

}


void loop()
{

}


//  -- END OF FILE --
