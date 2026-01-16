//
//    FILE: mcp4725_milliVolts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test mcp4725 lib
//     URL: https://github.com/RobTillaart/MCP4725


#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);

volatile int x;
uint32_t start, stop;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP4725_LIB_VERSION: ");
  Serial.println(MCP4725_LIB_VERSION);
  Serial.println();

  Wire.begin();

  MCP.begin();
  //  calibrate max voltage
  MCP.setMaxVoltage(5.1);

  Serial.print("\ngetMillisVolts:\t");
  Serial.println(MCP.getMillisVolts());
  Serial.println();

  //  just some random steps.
  for (float v = 1.22; v <= 5100; v *= 2)
  {
    Serial.print("setMilliVolts(");
    Serial.print(v);
    Serial.print(")\n");
    MCP.setMilliVolts(v);

    Serial.print("getMillisVolts:\t");
    Serial.println(MCP.getMillisVolts());
  }
  Serial.println();
}


void loop()
{
  //  triangle wave in milliVolts
  for (float v = 0.0; v <= 5100; v += 10)
  {
    MCP.setMilliVolts(v);
    delay(1);
  }
  for (float v = 5100; v >= 0.0; v -= 10)
  {
    MCP.setMilliVolts(v);
    delay(1);
  }
}


//  -- END OF FILE --
