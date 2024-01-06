//
//    FILE: skipFactorial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2024-01-06
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers....


uint32_t start, duration1, duration2, duration3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  int m = 300;
  int skip = 10;
  if (sizeof(double) == 8) m = 301;

  Serial.println("Skip factorial (n, 3)  -  max reached at n = 27, n = 45, n = 60");
  for (int i = 27; i < m; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(skipFactorial(i, skip));
    Serial.print('\t');
    Serial.print(print64(skipFactorial64(i, skip)));
    Serial.print('\t');
    Serial.print(sci(dSkipFactorial(i, skip), 15));
    Serial.println();
  }
  Serial.println();
  
  Serial.println("PERFORMANCE");
  Serial.println("n\tskipFactorial, skipFactorial64, dSkipFactorial usec\t values");
  delay(100);
  uint8_t n = 25;
  start = micros();
  double d1 = skipFactorial(n, 3);  //  will fail but indicative
  duration1 = micros() - start;
  start = micros();
  double d2 = skipFactorial64(n, 3);
  duration2 = micros() - start;
  start = micros();
  double d3 = dSkipFactorial(n, 3);
  duration3 = micros() - start;
  Serial.print(n);
  Serial.print('\t');
  Serial.print(duration1);
  Serial.print('\t');
  Serial.print('\t');
  Serial.print(duration2);
  Serial.print('\t');
  Serial.print('\t');
  Serial.print(duration3);
  Serial.println();
  Serial.print('\t');
  Serial.print(sci(d1, 10));
  Serial.print('\t');
  Serial.print(sci(d2, 10));
  Serial.print('\t');
  Serial.print(sci(d3, 10));
  Serial.println();

  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --
