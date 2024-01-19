//
//    FILE: AD5204_setPercentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-10-16
//     URL: https://github.com/RobTillaart/AD520X


#include "AD520X.h"

uint32_t start, stop;


//  select, reset, shutdown, data, clock == SOFTWARE SPI
//  AD5204 pot(10, 255, 255, 8, 9);
AD5204 pot = AD5204(10, 12, 13);     //  HW SPI by default


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();
  pot.begin(4);

  for (int p = 0; p <= 100; p++)
  {
    pot.setPercentage(0, p);
    float pp = pot.getPercentage(0);
    Serial.print(p);
    Serial.print('\t');
    Serial.print(pp, 1);
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
  start = millis();
  uint32_t i = 0;
  while (millis() - start < 10000)
  {
    float perc = 50 + sin(i * TWO_PI * 0.01) * 49.0;
    pot.setPercentage(0, perc);
    i++;
  }
  delay(1000);
}


//  -- END OF FILE --
