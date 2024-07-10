//
//    FILE: MCP4261_demo_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP4261


#include "MCP4261.h"


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

  for (int v = 0; v < 258; v++)
  {
    pot.setValue(1, v);
    int x = pot.getValueDevice(1);
    Serial.print(v);
    Serial.print("\t");
    Serial.println(x);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
