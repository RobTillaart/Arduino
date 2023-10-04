//
//    FILE: mcp9808_offset.ino
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
  delay(500);
  ts.setOffset(0);
  Serial.print(ts.getTemperature(), 4);
  ts.setOffset(random(200) * 0.01 - 1);  // add noise +- 1°C
  Serial.print('\t');
  Serial.println(ts.getTemperature(), 4);
}


// -- END OF FILE --
