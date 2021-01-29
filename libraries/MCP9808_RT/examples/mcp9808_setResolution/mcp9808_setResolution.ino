//
//    FILE: mcp9808_setResolution.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-11-13

#include "mcp9808.h"

MCP9808 ts(24);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}

void loop()
{
  for (int res = 0; res < 4; res++)
  {
    ts.setResolution(res);
    Serial.print(ts.getResolution());
    Serial.print('\t');
    delay(500);
    Serial.println(ts.getTemperature(), 4);
  }
}

// -- END OF FILE --
