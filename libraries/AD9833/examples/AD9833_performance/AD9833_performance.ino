//
//    FILE: AD9833_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-25
// PURPOSE: demo AD9833 wave form generator

#include "AD9833.h"

AD9833 AD;


uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  delay(10);

  AD.begin(7, 8, 9);  //  software SPI
  // AD.begin(10);   //  hardware SPI

  Serial.print("hardware:\t");
  Serial.println(AD.usesHWSPI());
  delay(10);

  start = micros();
  AD.setFrequency(1000, 0);
  stop = micros();
  Serial.print("setFrequency:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setPhase(45, 0);
  stop = micros();
  Serial.print("setPhase:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setWave(AD9833_SQUARE1);
  stop = micros();
  Serial.print("setWave:\t");
  Serial.println(stop - start);
  delay(10);
}


void loop()
{
}


//  -- END OF FILE --
