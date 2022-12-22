//    FILE: fastTrig_isincos256.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-09
// PURPOSE: R&D

#include "Arduino.h"
#include "FastTrig.h"

uint32_t start, stop;
volatile float x;
volatile int y;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  delay(10);

  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = (100 * sin(r));
  }
  stop = micros();
  Serial.print("SIN: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = (100 * isin(r));
  }
  stop = micros();
  Serial.print("ISIN: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);

  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    y = (100 * isin256(r)) >> 8;
  }
  stop = micros();
  Serial.print("ISIN256: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  Serial.println();
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = (100 * cos(r));
  }
  stop = micros();
  Serial.print("COS: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = (100 * icos(r));
  }
  stop = micros();
  Serial.print("ICOS: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);

  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    y = (100 * icos256(r)) >> 8;
  }
  stop = micros();
  Serial.print("ICOS256: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  Serial.println();
  delay(10);


  Serial.println("angle \tcos \tcos256 \tperc");
  for (uint32_t r = 0; r <= 360; r++)
  {
    x = (100 * cos(r * PI / 180.0));
    y = (100 * icos256(r)) >> 8;
    if (abs(x - y) >= 1)
    {
      Serial.print(r);
      Serial.print('\t');
      Serial.print(x);
      Serial.print('\t');
      Serial.print(float(y));
      Serial.print('\t');
      Serial.print(100.0 - 100.0 * float(y) / x);
      Serial.print("%");
      Serial.println();
    }
  }
  Serial.println();
  delay(100);

  volatile int sum = 0;
  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    sum += isin256(r) + icos256(r);
  }
  stop = micros();
  Serial.print("S C 256: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    int p, q;
    isincos256(r, &p, &q);
    sum += p + q;
  }
  stop = micros();
  Serial.print("ISINCOS256: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  for (uint32_t r = 0; r < 1000; r++)
  {
    int p, q, s, t;
    isincos256(r, &p, &q);
    s = isin256(r);
    t = icos256(r);
    if ((p != s) || (q != t))
    {
      Serial.print(r);
      Serial.print("\t");
      Serial.print(s);
      Serial.print("\t");
      Serial.print(p);
      Serial.print("\t");
      Serial.print(t);
      Serial.print("\t");
      Serial.print(q);
      Serial.println();
    }
  }
  delay(10);

  Serial.println("\ndone...");
}

void loop()
{
}


// -- END OF FILE --
