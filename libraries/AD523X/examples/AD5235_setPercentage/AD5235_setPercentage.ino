//
//    FILE: AD5235_setPercentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD523X


#include "AD523X.h"

uint32_t start, stop;


//  select, reset, dataIn, dataOut, clock == SOFTWARE SPI
//  AD5235 pot(10, 255, 7, 8, 9);  //  no reset.
AD5235 pot = AD5235(6, 7);     //  HW SPI by default


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();
  pot.begin(0);

  for (int p = 0; p <= 1000; p++)
  {
    pot.setPercentage(0, p * 0.1);
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
