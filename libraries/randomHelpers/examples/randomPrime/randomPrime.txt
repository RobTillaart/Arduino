//    FILE: randomPrime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show how to select random from an array of valid values.
//     URL: https://github.com/RobTillaart/Prandom


#include "Prandom.h"


Prandom R;

uint32_t start, stop;

const int NRVAL = 25;
uint8_t validValues[NRVAL] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("PRANDOM_LIB_VERSION: ");
  Serial.println(PRANDOM_LIB_VERSION);
  Serial.println();

  randomSeed(analogRead(0));
}


void loop()
{
  int number = validValues[R.randrange(NRVAL)];
  Serial.println(number);
  delay(1000);
}

//  -- END OF FILE --
