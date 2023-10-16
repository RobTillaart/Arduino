//
//    FILE: AD9850_ESP32_HWSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ESP32 hardware SPI
//     URL: https://github.com/RobTillaart/AD985X


#include "AD985X.h"

AD9850 freqGen;

uint32_t freq = 0;
uint32_t prev = 0;
uint32_t maxFreq;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  help();

  //  Select HW SPI for ESP32
  freqGen.selectHSPI();
  freqGen.begin(15, 16, 17);  //   selectPin, resetPin, FQUDPin

  freqGen.powerUp();
  maxFreq = freqGen.getMaxFrequency();
  Serial.println(maxFreq);
}


void loop()
{
  if (Serial.available() > 0)
  {
    int c = Serial.read();
    switch (c)
    {
      case '?' :
        help();
        break;
      case 'R' :
        freqGen.reset();
        freq = freqGen.getFrequency();
        break;
      case 'P' :
        freqGen.powerDown();
        break;
      case 'U' :
        freqGen.powerUp();
        break;
      case '+' :
        freq += 1;
        break;
      case '-' :
        freq -= 1;
        break;
      case '*' :
        freq *= 10;
        break;
      case '/' :
        freq /= 10;
        break;
    }
    if (freq > maxFreq) freq = maxFreq;
  }

  // UPDATE AD985X IF NEW VALUE
  if (prev != freq)
  {
    prev = freq;
    freqGen.setFrequency(freq);
    Serial.println(freq);
  }
}


void help()
{
  Serial.println();
  Serial.println("+ :  f = f + 1");
  Serial.println("- :  f = f - 1");
  Serial.println("* :  f = f * 10");
  Serial.println("/ :  f = f / 10");
  Serial.println("? :  help");
  Serial.println("R :  AD9850 reset");
  Serial.println("P :  AD9850 power down");
  Serial.println("U :  AD9850 power up");
  Serial.println();
}

// -- END OF FILE --
