//
//    FILE: AD985X_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo multi device
//     URL: https://github.com/RobTillaart/AD985X


/*
   Arduino              AND             AD985X
  --------------------------------------------------
  
                     +--------+
      (2) select ----| A      |
                     |      Q |------- FQ_UD   AD985X[0]
      (9) FQ_UD  ----| B      |
                     +--------+
  
                     +--------+
      (3) select ----| A      |
                     |      Q |------- FQ_UD   AD985X[1]
      (9) FQ_UD  ----| B      |
                     +--------+
  
                     +--------+
      (4) select ----| A      |
                     |      Q |------- FQ_UD   AD985X[2]
      (9) FQ_UD  ----| B      |
                     +--------+
*/


#include "AD985X.h"


// three AD9850 objects in an array
AD9850   freqGen[3]
{
  AD9850(2, 9, 8, 7, 6),
  AD9850(3, 9, 8, 7, 6),
  AD9850(4, 9, 8, 7, 6),
};


float    freq[3]     = { 25000, 30000, 40000 };
uint32_t previous[3] = { 0, 0, 0 };
uint32_t period[3]   = { 1000, 1100, 1200 };
uint32_t maxFreq     = 1000000;
uint32_t now;



void setup()
{
  // OPEN SERIAL for messages and debugging etc
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  // SPI.begin();  //  HW SPI

  //  initialize three devices
  for (int i = 0; i < 3; i++)
  {
    //  select, reset, fq_ud, data, clock
    freqGen[i].begin();
    freqGen[i].powerUp();
    freqGen[i].setFrequencyF(freq[i]);
  }

  maxFreq = freqGen[0].getMaxFrequency();
  Serial.print("MAXFREQ:\t");
  Serial.println(maxFreq);
}


void loop()
{
  now = millis();

  //  update any of the devices?
  for (int i = 0; i < 3; i++)
  {
    if ( now - previous[i] >= period[i] )
    {
      previous[i] = now;
      freq[i] += freq[i] * 0.01;
      if (freq[i] > maxFreq) freq[i] = 500;
      freqGen[i].setFrequencyF(freq[i]);
      Serial.print("FREQ ");
      Serial.print(i);
      Serial.print(" set to: ");
      Serial.println( (uint32_t) freq[i]);
    }
  }


}

//  -- END OF FILE --
