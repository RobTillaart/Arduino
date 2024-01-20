//
//    FILE: AD9850_ESP32_HWSPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ESP32 hardware SPI
//     URL: https://github.com/RobTillaart/AD985X


#include "AD985X.h"


#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif


//  HSPI uses default   SCLK=14, MISO=12, MOSI=13, SELECT=15
//  VSPI uses default   SCLK=18, MISO=19, MOSI=23, SELECT=5
SPIClass * myspi = new SPIClass(VSPI);
AD9850 freqGen(10, 9, 8, myspi, 18);  //  HW SPI  note the CLOCK pin param 18.
//  AD9850 freqGen(10, 9, 8, 7, 6);  //  SW SPI


uint32_t freq = 0;
uint32_t prev = 0;
uint32_t maxFreq;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  myspi->begin();

  freqGen.begin();

  freqGen.powerUp();
  maxFreq = freqGen.getMaxFrequency();
  Serial.println(maxFreq);

  help();
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
