//
//    FILE: MCP3002_analogRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP_ADC


#include "MCP_ADC.h"


MCP3002 mcp1;           //  use HWSPI
MCP3002 mcp2(6, 7, 8);  //  use SWSPI


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP_ADC_LIB_VERSION: ");
  Serial.println(MCP_ADC_LIB_VERSION);

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
  for (int channel = 0 ; channel < mcp1.channels(); channel++)
  {
    uint16_t val = mcp1.read(channel);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("mcp2:\t");
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    uint16_t val = mcp2.read(channel);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

