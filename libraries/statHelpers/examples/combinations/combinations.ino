//
//    FILE: combinations.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
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


  Serial.println("combinations(n, k)");
  delay(10);
  start = micros();
  for (int n = 0; n < 31; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      x = combinations(n, k);

      //      Serial.print(n);
      //      Serial.print('\t');
      //      Serial.print(k);
      //      Serial.print('\t');
      //      Serial.print(combinations(n, k));
      //      Serial.println();
    }
    // Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  Serial.println("rcombinations(n, k)");
  delay(10);
  start = micros();
  for (int n = 0; n < 31; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      x = rcombinations(n, k);

      //      Serial.print(n);
      //      Serial.print('\t');
      //      Serial.print(k);
      //      Serial.print('\t');
      //      Serial.print(combinations(n, k));
      //      Serial.println();
    }
    // Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  ///////////////////////////////////////////

  Serial.println("combinations64(n, k)");
  delay(10);
  start = micros();
  for (int n = 0; n < 62; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      x = combinations64(n, k);
      //      Serial.print(n);
      //      Serial.print('\t');
      //      Serial.print(k);
      //      Serial.print('\t');
      //      Serial.print(print64(combinations64(n, k)));
      //      Serial.println();
    }
    // Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  Serial.println("rcombinations64(n, k)");
  delay(10);
  start = micros();
  for (int n = 0; n < 62; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      x = rcombinations64(n, k);
      //      Serial.print(n);
      //      Serial.print('\t');
      //      Serial.print(k);
      //      Serial.print('\t');
      //      Serial.print(print64(combinations64(n, k)));
      //      Serial.println();
    }
    // Serial.println();
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println();

  ///////////////////////////////////////////

  Serial.println("dcombinations(n, k); ");
  delay(10);
  start = micros();
  int nmax = 125;
  if (sizeof(double) == 8) nmax = 1020;
  for (int n = nmax - 2; n < nmax +1; n++)
  {
    for (int k = n/2 -1 ; k <= n/2+1; k++)
    {
      x = dcombinations(n, k);
      //      Serial.print(n);
      //      Serial.print('\t');
      //      Serial.print(k);
      //      Serial.print('\t');
      //      Serial.print(comb(n, k));
      //      Serial.println();
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

