//
//    FILE: AD9833_sweep.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator
//     URL: https://github.com/RobTillaart/AD9833

#include "AD9833.h"


//  AD9833 AD(10);  //  HW SPI, select pin 10
//  comment  SPI.begin if HW SPI pins are used for SW SPI
//  AD9833 AD(10, 11, 13);  //  SW SPI, select, data , clock
AD9833 AD(5,6,7);  //  SW SPI, select, data , clock

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

  //  comment next line if HWSPI pins are used for SW SPI
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

  delay(10);  //  to simulate other tasks
}


//  -- END OF FILE --
