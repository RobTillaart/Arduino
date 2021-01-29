//
//    FILE: AD9851_demo_float.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo


#include "AD985X.h"


AD9851 freqGen; 

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

  freqGen.begin(10, 9, 8, 7, 6);
  freqGen.powerUp();
  maxFreq = freqGen.getMaxFrequency();
  Serial.println(maxFreq);
}


void loop()
{
  if (Serial.available() > 0)
  {
    int c = Serial.read();
    switch(c)
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
    freqGen.setFrequency(freq * 0.01);
    Serial.println(freq);
  }
}


void help()
{
  Serial.println();
  Serial.println("+ :  f = f + 0.01");
  Serial.println("- :  f = f - 0.01");
  Serial.println("* :  f = f * 10");
  Serial.println("/ :  f = f / 10");
  Serial.println("? :  help");
  Serial.println("R :  reset AD985X");
  Serial.println("P :  power down AD985X");
  Serial.println();
}

// END OF FILE
