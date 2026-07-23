//
//    FILE: termial.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"
#include "printHelpers.h"  //  to print large numbers....


uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  for (uint16_t n = 0; n < 65000; n += 1000)
  {
    Serial.print(n);
    Serial.print('\t');
    Serial.print(termial(n));
    Serial.print('\t');
    Serial.print(print64(termial64(n)));
    Serial.print('\t');
    Serial.print(sci(termialFloat(n), 10));
    Serial.print('\t');
    Serial.print(sci(termialFloat(n) - termial(n), 15));
    Serial.print('\t');
    Serial.println();
  }
  Serial.println();

  Serial.println("PERFORMANCE");
  Serial.println("n\ttermial,termialFloat usec\t values");
  delay(100);

  uint16_t x = analogRead(A0);
  start = micros();
  double d1 = termial(x);
  duration1 = micros() - start;
  start = micros();
  double d2 = termialFloat(x);
  duration2 = micros() - start;
  Serial.print(x);
  Serial.print('\t');
  Serial.print(duration1);
  Serial.print('\t');
  Serial.print(duration2);
  Serial.print('\t');
  Serial.print('\t');
  Serial.print(sci(d1, 10));
  Serial.print('\t');
  Serial.print(sci(d2, 10));
  Serial.println();
  Serial.println();


  Serial.println("RANGE");
  Serial.println("n\ttermialFloat \t values");
  delay(100);
  for (float x = 1; x < 1e21; x *= 10)
  {
    double value = termialFloat(x);
    Serial.print(sci(x, 10));
    Serial.print('\t');
    Serial.print(sci(value, 10));
    Serial.print('\t');
    Serial.print(sci((x/2)*(x+1), 10));
    Serial.println();
  }
  Serial.println("termialFloat is OK in terms of magnitude");
  Serial.println("Max input between 1e19~1e20");

  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --
