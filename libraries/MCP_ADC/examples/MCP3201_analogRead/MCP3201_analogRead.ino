//
//    FILE: MCP3201_analogRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP_ADC


#include "MCP_ADC.h"

MCP3201 mcp1;           //  use HWSPI
MCP3201 mcp2(6, 7, 8);  //  use SWSPI

uint32_t start, stop;

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
  delay(10);
  start = micros();
  uint16_t val = mcp1.read(0);
  stop = micros();
  Serial.print("hwspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

  Serial.print("mcp2\t");
  Serial.print(mcp2.channels());
  Serial.print("\t");
  Serial.println(mcp2.maxValue());
  delay(10);
  start = micros();
  val = mcp2.read(0);
  stop = micros();
  Serial.print("swspi:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(val);

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

  delay(5000);
}


//  -- END OF FILE --
