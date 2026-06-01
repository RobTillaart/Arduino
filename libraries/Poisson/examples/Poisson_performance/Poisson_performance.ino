//
//    FILE: Poisson_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/Poisson


#include "Poisson.h"

Poisson P(5);

uint32_t start, stop;

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("POISSON_LIB_VERSION: ");
  Serial.println(POISSON_LIB_VERSION);
  Serial.println();


  Serial.println("\nEQUAL");
  for (int k = 0; k <= 15; k++)
  {
    delay(100);
    start = micros();
    float p = P.equal(k);
    stop = micros();

    Serial.print(k);
    Serial.print("\t");
    Serial.print(p, 4);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }


  Serial.println("\nSMALLER EQUAL");
  for (int k = 0; k <= 15; k++)
  {
    delay(100);
    start = micros();
    float p = P.smallerEqual(k);
    stop = micros();

    Serial.print(k);
    Serial.print("\t");
    Serial.print(p, 4);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }

  Serial.println("\nBETWEEN");
  for (int k = 0; k <= 15; k++)
  {
    delay(100);
    start = micros();
    float p = P.between(k, 15);
    stop = micros();

    Serial.print(k);
    Serial.print("\t");
    Serial.print(p, 4);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\n");
  }

  Serial.println("\ndone...");
}


void loop(void)
{
}




//  -- END OF FILE --
