//
//    FILE: MCP3428_setChannel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to show the needed timeout between setChannel() and read()
//     URL: https://github.com/RobTillaart/MCP3424

#include "MCP3424.h"

MCP3428 mcp;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP3424_LIB_VERSION: ");
  Serial.println(MCP3424_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(10000);

  mcp.begin();

  //  dump configuration
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
  Serial.print("Mode:\t");
  Serial.println(mcp.getMode());
  Serial.println();
}


void loop()
{
  uint16_t del = mcp.getConversionDelay();

  //  sample all channels.
  for (int chan = 0; chan < mcp.getMaxChannels(); chan++)
  {
    mcp.setChannel(chan);
    //  new measurement duration depends on resolution. See readme.md.
    delay(del);
    Serial.print(mcp.read());
    Serial.print("\t");
    Serial.println(mcp.readVolts(), 6);
  }

  delay(1000);
}


//  -- END OF FILE --
