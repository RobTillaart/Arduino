//
//    FILE: mcp4725_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test mcp4725 lib
//     URL: https://github.com/RobTillaart/MCP4725
//
//  test to see behaviour when sensor is not connected and reconnected again. E.g. loose wires..


#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);

bool connected = false;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();

  if (MCP.begin() == false)
  {
    Serial.println("Could not find sensor");
  }

  Serial.println("end of setup()");
}


void loop()
{
  if (!connected && MCP.isConnected())
  {
    connected = true;
    Serial.print(millis());
    Serial.println("\tconnected");
  }
  if (connected && !MCP.isConnected())
  {
    connected = false;
  }
  delay(1000);
}


//  -- END OF FILE --

