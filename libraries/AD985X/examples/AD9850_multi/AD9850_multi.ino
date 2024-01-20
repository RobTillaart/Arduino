//
//    FILE: AD985X_multi.ino
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


//  we want to control three hardware devices
//  so we declare three software objects
//  in this case all using HW SPI.
AD9850 freqGen0(4, 9, 10, &SPI, 13);  //  13 is UNO SPI clock pin.
AD9850 freqGen1(2, 9, 10, &SPI, 13);
AD9850 freqGen2(3, 9, 10, &SPI, 13);

float    freq0 = 25000;
float    freq1 = 30000;
float    freq2 = 40000;
uint32_t maxFreq = 30000000;

uint32_t previousMillis0 = 0;
uint32_t previousMillis1 = 0;
uint32_t previousMillis2 = 0;

uint32_t period0 = 500;
uint32_t period1 = 1000;
uint32_t period2 = 2000;

uint32_t now;



void setup()
{
  //  OPEN SERIAL for messages and debugging etc
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  SPI.begin();

  //  initialize three devices
  freqGen0.begin();
  freqGen0.powerUp();
  freqGen1.begin();
  freqGen1.powerUp();
  freqGen2.begin();
  freqGen2.powerUp();

  //  MAXFREQ is the same for all devices
  maxFreq = freqGen0.getMaxFrequency();
  Serial.println(maxFreq);
}


void loop()
{
  //  get the time
  now = millis();

  //  do we need to update 0
  if (now - previousMillis0 >= period0)
  {
    previousMillis0 = now;
    freq0 = freq0 * 0.01;
    freqGen0.setFrequencyF(freq0 * 0.01);
    Serial.println( (uint32_t) freq0);
  }

  //  do we need to update 1
  if (now - previousMillis1 >= period1)
  {
    previousMillis1 = now;
    freq1 = freq1 * 0.01;
    freqGen1.setFrequencyF(freq1 * 0.01);
    Serial.println( (uint32_t) freq1);
  }

  //  do we need to update 2
  if (now - previousMillis2 >= period2)
  {
    previousMillis0 = now;
    freq2 = freq2 * 0.01;
    freqGen2.setFrequencyF(freq2 * 0.01);
    Serial.println( (uint32_t) freq2);
  }

}

//  -- END OF FILE --
