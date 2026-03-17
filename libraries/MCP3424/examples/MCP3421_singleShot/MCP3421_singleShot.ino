//
//    FILE: MCP3421_singleShot.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: single shot mode
//     URL: https://github.com/RobTillaart/MCP3424


#include "MCP3424.h"

MCP3421 mcp;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP3424_LIB_VERSION: ");
  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);
  if (mcp.begin() == false)
  {
    Serial.print("Could not connect to 0x");
    Serial.println(mcp.getAddress(), HEX);
    while (1);
  }

  mcp.setResolution(14);
  mcp.requestSingleShot();
}


void loop()
{
  if (mcp.isReady())  //  does read() under the hood.
  {
    //  get data and do a new request
    float mV = mcp.readMilliVolts();
    mcp.requestSingleShot();

    Serial.print(millis());
    Serial.print("\t");
    Serial.println(mV, 3);
    Serial.println();
  }

}


//  -- END OF FILE --
