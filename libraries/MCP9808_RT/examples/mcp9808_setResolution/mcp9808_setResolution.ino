//
//    FILE: mcp9808_setResolution.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-11-13


#include "mcp9808.h"

MCP9808 ts(24);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP9808_LIB_VERSION: ");
  Serial.println(MCP9808_LIB_VERSION);

  Wire.begin();
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
