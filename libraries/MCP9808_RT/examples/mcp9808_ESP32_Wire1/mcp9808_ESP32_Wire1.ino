//
//    FILE: mcp9808_ESP32_Wire1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP9808_RT


#include "mcp9808.h"

MCP9808 ts(24, &Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP9808_LIB_VERSION: ");
  Serial.println(MCP9808_LIB_VERSION);
  Serial.println();

  Wire1.begin(25, 26);  //  use Wire1 with adjusted pins.
}


void loop()
{
  delay(2000);
  Serial.println(ts.getTemperature(), 4);
}


//  -- END OF FILE --
