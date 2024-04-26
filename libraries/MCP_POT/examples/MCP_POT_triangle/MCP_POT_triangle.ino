//
//    FILE: MCP_POT_triangle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP_POT


#include "MCP_POT.h"


//  select, reset, shutdown, data, clock == SOFTWARE SPI
//  MCP_POT pot(10, 11, 12, 8, 9);

//  select, reset, shutdown, &SPI === HW SPI UNO clock = 13, data = 11
MCP_POT pot(5, 6, 7, &SPI);


long value = 0;
uint8_t pm = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();
  pot.begin();
}


void loop()
{
  for (int val = 0; val < 256; val++)
  {
    pot.setValue(0, val);
    pot.setValue(1, val);
    Serial.println(val);
    delay(100);
  }
  for (int val = 255; val > 0; val--)
  {
    //  both should work too.
    pot.setValue(val);
    Serial.println(val);
    delay(100);
  }
}


//  -- END OF FILE --
