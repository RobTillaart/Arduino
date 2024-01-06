//
//    FILE: bigCombinations.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-08-06
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"


uint32_t start, duration1;
volatile uint32_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  Serial.println("dcombinations(n, k); ");
  delay(10);
  start = micros();
  uint32_t nmax = 125;
  if (sizeof(double) == 8) nmax = 1020;
  for (int n = nmax - 2; n < nmax + 1; n++)
  {
    for (int k = n / 2 - 1 ; k <= n / 2 + 1; k++)
    {
      double xx = dcombinations(n, k);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(sci(xx, 15));
      Serial.println();
    }
    //Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();


  Serial.println("bigCombinations(n, k, mant, expo); ");
  delay(10);
  start = micros();
  nmax = 10000000;
  for (uint32_t n = nmax - 2; n < nmax + 1; n++)
  {
    for (uint32_t k = n / 2 - 1 ; k <= n / 2 + 1; k++)
    {
      double   mant = 0;
      uint32_t expo = 0;
      bigCombinations(n, k, mant, expo);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(mant, 15);
      Serial.print('E');
      Serial.print(expo);
      Serial.println();
    }
    // Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

