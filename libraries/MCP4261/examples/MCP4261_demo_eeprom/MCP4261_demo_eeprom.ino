//
//    FILE: MCP4261_demo_eeprom.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MCP4261


#include "MCP4261.h"


//  select, shutdown, dataIn, dataOut, clock == SOFTWARE SPI
//  MCP4261 pot(10, 6, 7, 8, 9);

//  select, shutdown, &SPI === HW SPI UNO clock = 13, dataOut = 11
MCP4261 pot(10, 6, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();

  pot.begin();

  for (int address = 0; address < 10; address++)
  {
    Serial.print(address);
    Serial.print("\t");
    Serial.println(pot.getEEPROM(address));
  }

  for (int address = 0; address < 10; address++)
  {
    int x = random(512);
    pot.setEEPROM(address, x);
    delay(20);
    Serial.println(x);
  }

  for (int address = 0; address < 10; address++)
  {
    Serial.print(address);
    Serial.print("\t");
    Serial.println(pot.getEEPROM(address));
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
