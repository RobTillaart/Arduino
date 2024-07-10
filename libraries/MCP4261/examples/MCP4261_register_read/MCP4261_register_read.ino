//
//    FILE: MCP4261_register_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP4261
//
//  Works when readRegister() is made public.
//  meant for testing only.

#include "MCP4261.h"


uint32_t start, stop;


//  select, shutdown, dataIn, dataOut, clock == SOFTWARE SPI
// MCP4261 pot(10, 6, 7, 8, 9);

//  select, shutdown, &SPI === HW SPI UNO clock = 13, dataOut = 11
MCP4261 pot(10, 6, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();

  pot.begin();

  for (int r = 0; r < 16; r++)
  {
    Serial.print(r);
    Serial.print("\t");
    Serial.println(pot.readRegister(r));
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
