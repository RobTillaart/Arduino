//
//    FILE: MCP3002_analogRead.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo
//    DATE: 2020-08-13

#include "MCP_ADC.h"

MCP3002 mcp1;       // use HWSPI
MCP3002 mcp2(6, 7); // use SWSPI

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

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
}

void loop()
{
  Serial.print("mcp1:\t");
  for (int channel = 0 ; channel < mcp1.channels(); channel++)
  {
    uint16_t val = mcp1.analogRead(channel);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("mcp2:\t");
  for (int channel = 0 ; channel < mcp2.channels(); channel++)
  {
    uint16_t val = mcp2.analogRead(channel);
    Serial.print(val);
    Serial.print("\t");
  }
  Serial.println();

  delay(1000);
}

// -- END OF FILE --
