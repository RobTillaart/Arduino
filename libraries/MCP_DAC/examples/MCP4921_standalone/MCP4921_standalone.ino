//
//    FILE: MCP4921_standalone.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: faster no checking MCP4921 specific code
//     URL: https://github.com/RobTillaart/MCP_DAC


#include "SPI.h"

#define MCP4921_CS_PIN    10

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(MCP4921_CS_PIN, OUTPUT);
  digitalWrite(MCP4921_CS_PIN, HIGH);

  SPI.begin();

  performance_test();
  analogWrite_test();
}


void mcp4921(uint16_t value)
{
  uint16_t data = 0x3000 | value;
  digitalWrite(MCP4921_CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
  SPI.transfer((uint8_t)(data >> 8));
  SPI.transfer((uint8_t)(data & 0xFF));
  SPI.endTransaction();
  digitalWrite(MCP4921_CS_PIN, HIGH);
}


void analogWrite_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (uint16_t value = 0; value < 4096; value += 0xFF)
  {
    mcp4921(value);
    Serial.print(value);
    Serial.print("\t");
    Serial.println(analogRead(A0));
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
    mcp4921(value);
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

