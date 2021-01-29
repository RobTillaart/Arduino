//
//    FILE: AD9851_manual update.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo


#include "AD985X.h"


AD9851 freqGen;

uint32_t freq    = 0;
uint32_t maxFreq = 2000000UL;

bool up = true;

uint32_t lastUpdate = 0;

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

  Serial.print("AutoUpdate: ");
  Serial.println(freqGen.getAutoUpdate());
  freqGen.setAutoUpdate(false);
  Serial.print("AutoUpdate: ");
  Serial.println(freqGen.getAutoUpdate());
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

  // only update once per second
  // effectively have a random frequency
  if (millis() - lastUpdate >= 1000)
  {
    lastUpdate = millis();
    freqGen.update();
    Serial.print(millis());
    Serial.print('\t');
    Serial.println(freq);
  }
}

// -- END OF FILE --
