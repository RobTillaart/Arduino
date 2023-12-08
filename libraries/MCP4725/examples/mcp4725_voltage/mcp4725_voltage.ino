//
//    FILE: mcp4725_voltage.ino
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
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP4725_VERSION: ");
  Serial.println(MCP4725_VERSION);

  Wire.begin();

  MCP.begin();
  //  calibrate max voltage
  MCP.setMaxVoltage(5.1);  

  Serial.print("\nVoltage:\t");
  Serial.println(MCP.getVoltage());
  Serial.println();

  for (float v = 0.0; v <= 5.1; v += 0.1)
  {
    Serial.print("setVoltage(");
    Serial.print(v);
    Serial.print(")\n");
    MCP.setVoltage(v);
    
    Serial.print("getVoltage:\t");
    Serial.println(MCP.getVoltage());
  }
  Serial.println();
}





void loop()
{
  //  triangle wave
  for (float v = 0.0; v <= 5.1; v += 0.01)
  {
    MCP.setVoltage(v);
    delay(1);
  }
  for (float v = 5.1; v >= 0.0; v -= 0.01)
  {
    MCP.setVoltage(v);
    delay(1);
  }
}


//  -- END OF FILE --
