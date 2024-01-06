//
//    FILE: permutations.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-08-06
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"


uint32_t start, duration1, duration2;
volatile uint32_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();


  ///////////////////////////////////////////

  Serial.println("permutations64(n, k)");
  start = micros();
  for (int n = 0; n < 20; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      // x = permutations64(n, k);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(print64(permutations64(n, k)));
      Serial.println();
    }
    Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  ///////////////////////////////////////////
  // 
  // tests are commented as they take serious time.

  /*
    Serial.println("dpermutations(n, k) - double can be 4 or 8 bit.");
    start = micros();
    int nmax = 34;
    if (sizeof(double) == 8) nmax = 170;  // Exponent overflow in double
    for (int n = 0; n <= nmax; n++)
    {
    for (int k = 0; k <= n; k++)
    {
      // x = dpermutations(n, k);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(sci(dpermutations(n, k), 15));
      Serial.println();
    }
    Serial.println();
    }
    duration1 = micros() - start;
    Serial.println(duration1);
    Serial.println();
  */

  /*  takes 40 seconds ...
    Serial.println("bigPermutations(n, k, mant, expo)");
    start = micros();
    nmax = 30;
    // if (sizeof(double) == 8) nmax = 170;
    for (int n = 0; n <= nmax; n++)
    {
    for (int k = 0; k <= n; k++)
    {
      double   mant = 0;
      uint32_t expo = 0;
      bigPermutations(n, k, mant, expo);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(mant, 15);
      Serial.print('E');
      Serial.print(expo);
      Serial.println();
    }
    Serial.println();
    }
    duration1 = micros() - start;
    Serial.println(duration1);
    Serial.println();
  */

  /*
  Serial.println("bigPermutations(n, k, mant, expo)");
  start = micros();
  for (int n = 1000; n <= 10000; n += 1000)
  {
    for (int k = 0; k <= n; k += n / 4)
    {
      double   mant = 0;
      uint32_t expo = 0;
      bigPermutations(n, k, mant, expo);
      Serial.print(n);
      Serial.print('\t');
      Serial.print(k);
      Serial.print('\t');
      Serial.print(mant, 15);
      Serial.print('E');
      Serial.print(expo);
      Serial.println();
    }
    Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();
  */


  //  pick 1000 persons from 4294967295  (maxLong)
  double   mant = 0;
  uint32_t expo = 0;
  bigPermutations(4294967295, 1000, mant, expo);
  Serial.print(mant, 15);
  Serial.print('E');
  Serial.print(expo);
  Serial.println();

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

