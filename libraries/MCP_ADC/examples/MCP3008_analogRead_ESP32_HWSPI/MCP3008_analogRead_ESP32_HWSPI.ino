//
//    FILE: MCP3008_analogRead_ESP32_HWSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP_ADC


#include "MCP_ADC.h"


// ESP32 PINS
// For HSPI
//   CLK:  14
//   MOSI: 13
//   MISO: 12
//
// For VSPI (id = 2):
//   CLK:  18,
//   MOSI: 23,
//   MISO: 19,

SPIClass * mySPI = new SPIClass(VSPI);  //  or HSPI

MCP3008 mcp1(mySPI);           //  use HWSPI on ESP32 (apparently VSPI)
// MCP3008 mcp1(23, 19, 21);   //  ESP32 use SWSPI  dataIn, dataOut, Clock
// MCP3008 mcp1(6, 7, 8);      //  UNO   use SWSPI  dataIn, dataOut, Clock


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP_ADC_LIB_VERSION: ");
  Serial.println(MCP_ADC_LIB_VERSION);

  SPI.begin();

  mcp1.begin(5);                //  chip select pin.

  Serial.println();
  Serial.println("ADC\tCHAN\tMAXVALUE");
  Serial.print("mcp1\t");
  Serial.print(mcp1.channels());
  Serial.print("\t");
  Serial.println(mcp1.maxValue());

  mcp1.setSPIspeed(4000000);  //  seems to be the max speed. use 1MHz (default) to be safe
}


void loop()
{
  Serial.print(millis());
  Serial.print("\tmcp1:\t");
  for (int channel = 0 ; channel < mcp1.channels(); channel++)
  {
    uint16_t val = mcp1.read(channel);
    Serial.print(val);
    Serial.print("\t");
    delay(1);       //  added so single reads are better visible on a scope
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

