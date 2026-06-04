//
//    FILE: Poisson_add.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behavior
//     URL: https://github.com/RobTillaart/Poisson


#include "Poisson.h"

Poisson P(5);

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("POISSON_LIB_VERSION: ");
  Serial.println(POISSON_LIB_VERSION);
  Serial.println();

  for (int k = 0; k <= 15; k++)
  {
    Serial.print(k);
    Serial.print("\t");
    Serial.print(P.equal(k), 4);
    Serial.print("\t");
    Serial.println(P.smallerEqual(k), 4);
  }
  Serial.print("P.average:\t");
  Serial.println(P.average(), 3);
  Serial.print("P.stdev:\t");
  Serial.println(P.stdev(), 3);

  Serial.println("\n now adjust mu with 20 (dummy) events..");
  for (int n = 1; n <= 20; n++)
  {
    P.add(n, 0.5 / n);  //  different weights.
  }

  for (int k = 0; k <= 15; k++)
  {
    Serial.print(k);
    Serial.print("\t");
    Serial.print(P.equal(k), 4);
    Serial.print("\t");
    Serial.println(P.smallerEqual(k), 4);
  }
  Serial.print("P.average:\t");
  Serial.println(P.average(), 3);
  Serial.print("P.stdev:\t");
  Serial.println(P.stdev(), 3);

  Serial.println("\ndone...");
}


void loop(void)
{
}




//  -- END OF FILE --
