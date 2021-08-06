//
//    FILE: semiFactorial.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-08-05
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  // to print large numbers....


uint32_t start, duration1, duration2, duration3;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  int m = 60;
  if (sizeof(double) == 8) m = 301;

  for (int i = 0; i < m; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(semiFactorial(i));
    Serial.print('\t');
    Serial.print(print64(semiFactorial64(i)));
    Serial.print('\t');
    Serial.print(sci(dSemiFactorial(i), 15));
    Serial.println();
  }
  Serial.println();
  
  Serial.println("PERFORMANCE");
  Serial.println("n\tsemiFactorial, semiFactorial64, dSemiFactorial usec\t values");
  delay(100);
  uint8_t n = 25;
  start = micros();
  double d1 = semiFactorial(n);  // will fail but indicative
  duration1 = micros() - start;
  start = micros();
  double d2 = semiFactorial64(n);
  duration2 = micros() - start;
  start = micros();
  double d3 = dSemiFactorial(n);
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

// -- END OF FILE --
