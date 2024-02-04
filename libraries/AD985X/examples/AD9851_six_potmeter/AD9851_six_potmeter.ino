//
//    FILE: AD9851_six_potmeter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD985X


#include "AD985X.h"


AD9851 freqGen(10, 9, 8, 7, 6);  //  SW SPI
//  AD9851 freqGen(10, 9, 8, &SPI, 6);  //  HW SPI


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  // SPI.begin();  //  HW SPI

  freqGen.begin();
}


void loop()
{
  float freq = readFreq(true);

  freqGen.setFrequencyF(freq);
  Serial.println(freq);
  delay(1000);
}


float readFreq(bool KHZ)
{
  float freq = 0;
  freq += (analogRead(A0) / 103) * 1000;
  freq += (analogRead(A1) / 103) * 100;
  freq += (analogRead(A2) / 103) * 10;
  freq += (analogRead(A3) / 103) * 1;
  freq += (analogRead(A4) / 103) * 0.1;
  freq += (analogRead(A5) / 103) * 0.01;

  if (KHZ) freq *= 1000;
  return freq;
}

//  -- END OF FILE --
