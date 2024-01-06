//
//    FILE: factorial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers....


uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();


  int m = 35;
  if (sizeof(double) == 8) m = 175;

  for (int i = 0; i < m; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(factorial(i));
    Serial.print('\t');
    Serial.print(print64(factorial64(i)));
    Serial.print('\t');
    Serial.print(sci(dfactorial(i), 15));
    Serial.print('\t');
    Serial.print(sci(stirling(i), 15));
    Serial.print('\t');
    Serial.println();
  }
  Serial.println();

  Serial.println("PERFORMANCE");
  Serial.println("n\tdfactorial,stirling usec\t values");
  delay(100);
  start = micros();
  double d1 = dfactorial(25);
  duration1 = micros() - start;
  start = micros();
  double d2 = stirling(25);
  duration2 = micros() - start;
  Serial.print(25);
  Serial.print('\t');
  Serial.print(duration1);
  Serial.print('\t');
  Serial.print(duration2);
  Serial.print('\t');
  Serial.print('\t');
  Serial.print('\t');
  Serial.print(sci(d1, 10));
  Serial.print('\t');
  Serial.print(sci(d2, 10));
  Serial.println();

  if (sizeof(double) == 8)
  {
    delay(100);
    start = micros();
    d1 = dfactorial(143);
    duration1 = micros() - start;
    start = micros();
    d2 = stirling(143);
    duration2 = micros() - start;
    Serial.print(143);
    Serial.print('\t');
    Serial.print(duration1);
    Serial.print('\t');
    Serial.print(duration2);
    Serial.print('\t');
    Serial.print('\t');
    Serial.print('\t');
    Serial.print(sci(d1, 10));
    Serial.print('\t');
    Serial.print(sci(d2, 10));
    Serial.println();
  }

  Serial.println("\nStirling() is pretty constant but less exact");
  Serial.println("\ndFactorial is just n multiplications, and pretty exact");

  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --

