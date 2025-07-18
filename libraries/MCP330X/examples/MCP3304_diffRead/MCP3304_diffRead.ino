//
//    FILE: MCP3304_differentialRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP330X


#include "MCP330X.h"


MCP3304 mcp1;           //  use HWSPI
MCP3304 mcp2(6, 7, 8);  //  use SWSPI


void setup()
{
  //  while (!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MCP330X_LIB_VERSION: ");
  Serial.println(MCP330X_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mcp1.begin(10);
  mcp2.begin(5);

  Serial.println();
  Serial.println("ADC\tCHAN\tMAXVALUE");
  Serial.print("mcp1\t");
  Serial.print(mcp1.channels());
  Serial.print("\t");
  Serial.println(mcp1.maxValue());
  Serial.print("mcp2\t");
  Serial.print(mcp2.channels());
  Serial.print("\t");
  Serial.println(mcp2.maxValue());
  Serial.println();
}


void loop()
{
  Serial.print("mcp1:\t");
  for (int pair = 0; pair < mcp1.channels(); pair++)
  {
    int16_t val = mcp1.differentialRead(pair);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("mcp2:\t");
  for (int pair = 0; pair < mcp2.channels(); pair++)
  {
    int16_t val = mcp2.differentialRead(pair);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

