//
//    FILE: FractionFindSum.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 13-feb-2015
//     URL:
//
// Released to the public domain
//

#include "fraction.h"

uint32_t start;
uint32_t stop;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.print("\n\nStart F: ");
  Serial.println(FRACTIONLIBVERSION);
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
  Fraction z(0);

  Serial.print(f);
  Serial.print(" =\t ");
  for (long i = 1; i < 10000; i++)
  {
    Fraction g(1, i);
    if (g <= f)
    {
      f -= g;
      z += g;
      Serial.print(g);
      Serial.print(" + ");
    }
    if (f == 0)
    {
      break;
    }
  }
  Serial.print("\t => ");
  Serial.println(z);
  Serial.println();
}
void loop()
{
}


