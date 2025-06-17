//
//    FILE: AD7390_setVoltage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo voltage functions
//     URL: https://github.com/RobTillaart/AD7390


#include "AD7390.h"

uint32_t start;


//  select, reset, data, clock == SOFTWARE SPI
//  AD7390 myDAC(6, 7, 11, 13);

//  select, reset, &SPI === HW SPI UNO clock = 13, data = 11
AD7390 myDAC(6, 7, &SPI);


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7390_LIB_VERSION: ");
  Serial.println(AD7390_LIB_VERSION);
  Serial.println();


  SPI.begin();
  myDAC.begin(0);

  for (int p = 0; p <= 100; p++)
  {
    myDAC.setPercentage(p);
    float pp = myDAC.getPercentage();
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
    myDAC.setPercentage(perc);
    i++;
  }
  delay(1000);
}


//  -- END OF FILE --
