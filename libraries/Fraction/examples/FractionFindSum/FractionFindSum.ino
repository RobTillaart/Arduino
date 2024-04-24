//
//    FILE: FractionFindSum.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo fraction math.
//     URL: https://github.com/RobTillaart/Fraction
//
//  Find a sum of fractions that (within accuracy) 
//       adds up to a given fraction.
//

#include "fraction.h"


uint32_t start;
uint32_t stop;


void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.print("\n\nStart F: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();
  randomSeed(analogRead(A0) * 256 + analogRead(A1));

  start = micros();
  stop = micros();
  // Serial.println(stop - start);

  for (int i = 1; i < 93; i++)
  {
    Fraction f(i, 93);
    findSum(f);
  }
}


void findSum(Fraction f)
{
  Fraction z(0, 1);

  Serial.print(f.toString());
  Serial.print(" =\t ");
  for (long i = 1; i < 10000; i++)
  {
    Fraction g(1, i);
    if (g <= f)
    {
      f -= g;
      z += g;
      Serial.print(g.toString());
      Serial.print(" + ");
    }
    if (f == Fraction(0, 1))
    {
      break;
    }
  }
  Serial.print("\t => ");
  Serial.println(z.toString());
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
