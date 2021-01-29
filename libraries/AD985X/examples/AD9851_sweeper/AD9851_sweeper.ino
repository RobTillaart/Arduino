//
//    FILE: AD9851_sweeper.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo


#include "AD985X.h"


AD9851 freqGen;

uint32_t freq    = 0;
uint32_t maxFreq = 2000000UL;

bool up = true;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  freqGen.begin(10, 9, 8, 7, 6);
  freqGen.powerUp();
  freqGen.setAutoRefClock(true);

  freq = 100;
}


void loop()
{
  if (up == true) freq *= 1.01;
  else            freq /= 1.01;

  if (freq > maxFreq)
  {
    freq = maxFreq;
    up = false;
  }
  if (freq < 100)
  {
    freq = 100;
    up = true;
  }
  freqGen.setFrequency(freq);
  Serial.print(millis());
  Serial.print('\t');
  Serial.println(freq);
  delay(50);
}

// -- END OF FILE --
