//
//    FILE: mcp9808_minimum.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-11-12

#include "mcp9808.h"

MCP9808 ts(24);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}

void loop()
{
  delay(2000);
  Serial.println(ts.getTemperature(), 4);
}

// -- END OF FILE --
