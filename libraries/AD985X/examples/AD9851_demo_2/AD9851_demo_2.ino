//
//    FILE: AD9851_demo_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD985X


#include "AD985X.h"


AD9851 freqGen(10, 9, 8, 7, 6);  //  SW SPI
//  AD9851 freqGen(10, 9, 8, &SPI, 6);  //  HW SPI

uint32_t freq = 0;
uint32_t prev = 0;
uint32_t maxFreq;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AD985X_LIB_VERSION: \t");
  Serial.println(AD985X_LIB_VERSION);

  // SPI.begin();  //  HW SPI

  freqGen.begin();

  freqGen.powerUp();
  maxFreq = freqGen.getMaxFrequency();
  Serial.print(" MAX_FREQ: ");
  Serial.println(maxFreq);
  Serial.print("REF_CLOCK: ");
  Serial.println(freqGen.getRefClock());

  help();
}


void loop()
{
  if (Serial.available() > 0)
  {
    int c = Serial.read();
    switch (c)
    {
      case '0'...'9' :
        freq *= 10;
        freq += c - '0';
        break;
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
      case 'A' :
        freqGen.setAutoRefClock(true);
        Serial.println("REF_CLOCK: AUTO ON");
        break;
      case 'C' :
        freqGen.setAutoRefClock(false);
        Serial.println("REF_CLOCK: AUTO OFF");
        break;
      case 'G' :
        Serial.print("REF_CLOCK: ");
        Serial.println(freqGen.getRefClock());
        break;
      case 'H' :
        freqGen.setRefClockHigh();
        Serial.print("REF_CLOCK: ");
        Serial.println(freqGen.getRefClock());
        break;
      case 'L' :
        freqGen.setRefClockLow();
        Serial.print("REF_CLOCK: ");
        Serial.println(freqGen.getRefClock());
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

  //  update device if frequency has changed
  if (prev != freq)
  {
    prev = freq;

    freqGen.setFrequency(freq);
    freq = freqGen.getFrequency();
    Serial.println(freq);
    //  printFreq(freq);
  }
}


void help()
{
  Serial.println();
  Serial.println("     HELP AD985X");
  Serial.println("+ :  freq = freq + 1");
  Serial.println("- :  freq = freq - 1");
  Serial.println("* :  freq = freq * 10");
  Serial.println("/ :  freq = freq / 10");
  Serial.println("? :  help");
  Serial.println("R :  AD9851 reset");
  Serial.println("P :  AD9851 power down");
  Serial.println("U :  AD9851 power up");
  Serial.println("A :  AD9851 set reference clock AUTO ON");
  Serial.println("C :  AD9851 set reference clock AUTO OFF");
  Serial.println("G :  AD9851 print reference clock");
  Serial.println("H :  AD9851 set reference clock HIGH");
  Serial.println("L :  AD9851 set reference clock LOW");
  Serial.println();
}


void printFreq(float freq)
{
  if (freq > 1000000)
  {
    Serial.print(freq / 1e6, 2);
    Serial.println(" MHz");
    return;
  }

  if (freq > 1000)
  {
    Serial.print(freq / 1e3, 2);
    Serial.println(" KHz");
    return;
  }
  Serial.print(freq, 2);
  Serial.println(" Hz");
}

//  -- END OF FILE --
