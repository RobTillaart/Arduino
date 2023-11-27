//
//    FILE: AD9833_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-25
// PURPOSE: demo AD9833 wave form generator


#include "AD9833.h"


//  AD9833 AD(10, 11, 13);  //  software SPI
AD9833 AD(10);       //  hardware SPI


uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  delay(10);

  AD.begin();

  Serial.print("hardware:\t");
  Serial.println(AD.usesHWSPI());
  delay(10);

  start = micros();
  AD.setFrequency(2000, 0);
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
