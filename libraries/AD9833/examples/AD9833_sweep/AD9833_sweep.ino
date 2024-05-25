//
//    FILE: AD9833_sweep.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator
//     URL: https://github.com/RobTillaart/AD9833

#include "AD9833.h"


AD9833 AD(10);  //  HW SPI, select pin 10

int freq = 100;
bool up = true;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  Serial.println();

  SPI.begin();
  AD.begin();
  AD.setWave(AD9833_SINE);
}


void loop()
{
  if (up) freq++;
  else freq--;
  //  reverse direction if needed
  if (freq >= 1000) up = false;
  if (freq <= 100) up = true;
  AD.setFrequency(freq);

  delay(100);  //  to simulate other tasks
}


//  -- END OF FILE --
