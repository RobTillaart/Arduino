//
//    FILE: MCP4922_standalone.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: faster no checking MCP4922 specific code
//     URL: https://github.com/RobTillaart/MCP_DAC


#include "SPI.h"

#define MCP4922_CS_PIN    10

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  //  Serial.print("MCP_DAC_LIB_VERSION: ");
  //  Serial.println(MCP_DAC_LIB_VERSION);
  Serial.println();

  pinMode(MCP4922_CS_PIN, OUTPUT);
  digitalWrite(MCP4922_CS_PIN, HIGH);

  SPI.begin();

  performance_test();
  analogWrite_test();
}


void mcp4922(uint16_t value, uint8_t channel)  //  channel = 0, 1
{
  uint16_t data = 0x3000 | value;
  if (channel == 1) data |= 0x8000;
  digitalWrite(MCP4922_CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  SPI.transfer((uint8_t)(data >> 8));
  SPI.transfer((uint8_t)(data & 0xFF));
  SPI.endTransaction();
  digitalWrite(MCP4922_CS_PIN, HIGH);
}


void analogWrite_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (uint16_t value = 0; value < 4096; value += 0xFF)
  {
    mcp4922(value, 0);
    Serial.print(value);
    Serial.print("\t");
    Serial.println(analogRead(A0));  //  connect DAC output to ADC input
    delay(10);
  }
  Serial.println();

  for (uint16_t value = 0; value < 4096; value += 0xFF)
  {
    mcp4922(value, 1);
    Serial.print(value);
    Serial.print("\t");
    Serial.println(analogRead(A1));  //  connect DAC output to ADC input
    delay(10);
  }
}


void performance_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  start = micros();
  for (uint16_t value = 0; value < 4096; value++)
  {
    mcp4922(value, 0);
  }
  stop = micros();
  Serial.print("4096 calls:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 4096.0 );
  delay(10);

  start = micros();
  for (uint16_t value = 0; value < 4096; value++)
  {
    mcp4922(value, 1);
  }
  stop = micros();
  Serial.print("4096 calls:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 4096.0 );
  delay(10);
}


void loop()
{
}


//  -- END OF FILE --
