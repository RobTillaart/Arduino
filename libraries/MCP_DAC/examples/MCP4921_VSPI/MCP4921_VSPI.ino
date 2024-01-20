//
//    FILE: MCP4921_VSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP_DAC lib
//     URL: https://github.com/RobTillaart/MCP_DAC


#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif


#include "MCP_DAC.h"


//  HSPI uses default   SCLK=14, MISO=12, MOSI=13, SELECT=15
//  VSPI uses default   SCLK=18, MISO=19, MOSI=23, SELECT=5
SPIClass * myspi = new SPIClass(VSPI);
MCP4921 MCP(myspi);  // HW SPI


volatile int x;
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  myspi->begin();

  MCP.begin(5);         //  5 for VSPI and 15 for HSPI

  Serial.print("MCP_DAC_LIB_VERSION: ");
  Serial.println(MCP_DAC_LIB_VERSION);
  Serial.println();
  Serial.print("CHANNELS:\t");
  Serial.println(MCP.channels());
  Serial.print("MAXVALUE:\t");
  Serial.println(MCP.maxValue());
  delay(100);

  // MCP.setSPIspeed(100000);  //  for slower scopes
  performance_test();

  Serial.println("\nDone...");
}


void performance_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  start = micros();
  for (uint16_t value = 0; value < MCP.maxValue(); value++)
  {
    x = MCP.write(value, 0);
  }
  stop = micros();
  Serial.print(MCP.maxValue());
  Serial.print(" x MCP.write():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / (MCP.maxValue() + 1.0) );
  delay(10);

  start = micros();
  for (uint16_t value = 0; value < MCP.maxValue(); value++)
  {
    MCP.fastWriteA(value);
  }
  stop = micros();
  Serial.print(MCP.maxValue());
  Serial.print(" x MCP.fastWriteA():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / (MCP.maxValue() + 1.0) );
  delay(10); 
}


void loop()
{
  performance_test();
}


//  -- END OF FILE --

