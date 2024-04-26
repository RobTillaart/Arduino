//
//    FILE: MCP_POT_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure setValue() at various SPI speeds.
//     URL: https://github.com/RobTillaart/MCP_POT


#include "MCP_POT.h"


//  select, reset, shutdown, data, clock == SOFTWARE SPI
//  MCP_POT pot(10, 11, 12, 8, 9);

//  select, reset, shutdown, &SPI === HW SPI UNO clock = 13, data = 11
MCP_POT pot(5, 6, 7, &SPI);


long value = 0;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP_POT_LIB_VERSION: ");
  Serial.println(MCP_POT_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();
  pot.begin();


  Serial.println("\nONE POTMETERS\n");
  delay(100);
  //  8 MHz is max speed UNO, adjust for other platforms.
  for (uint32_t speed = 1; speed <= 8; speed++)
  {
    pot.setSPIspeed(speed * 1000000UL);
    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      pot.setValue(0, i & 0xFF);
    }
    stop = micros();
    Serial.print(speed * 1000000);
    Serial.print("\t");
    Serial.print((stop - start) * 0.001, 2);
    Serial.println(" us");
    delay(100);
  }

  Serial.println("\nBOTH POTMETERS\n");
  delay(100);
  for (uint32_t speed = 1; speed <= 8; speed++)
  {
    pot.setSPIspeed(speed * 1000000UL);
    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      //  no pm selected => both
      pot.setValue(i & 0xFF);
    }
    stop = micros();
    Serial.print(speed * 1000000);
    Serial.print("\t");
    Serial.print((stop - start) * 0.001, 2);
    Serial.println(" us");
    delay(100);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
