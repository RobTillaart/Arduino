//    FILE: isincos.ino
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
    x = sin(r);
  }
  stop = micros();
  Serial.print("SIN: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = isin(r);
  }
  stop = micros();
  Serial.print("ISIN: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);

  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = cos(r);
  }
  stop = micros();
  Serial.print("COS: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);


  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    x = icos(r);
  }
  stop = micros();
  Serial.print("ICOS: \t\t");
  Serial.print(stop - start);
  Serial.println(" us");
  delay(10);

  for (uint32_t r = 0; r <= 360; r++)
  {
    x = cos(r * (PI / 180.0));
    y = icos(r);
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

  volatile float sum = 0;
  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    sum += sin(r * (PI / 180.0)) + cos(r * (PI / 180.0));
  }
  stop = micros();
  Serial.print("SIN + COS: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  Serial.println(sum, 4);
  delay(10);

  sum = 0;
  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    sum += isin(r) + icos(r);
  }
  stop = micros();
  Serial.print("ISIN + ICOS: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  Serial.println(sum, 4);
  delay(10);

  sum = 0;
  start = micros();
  for (uint32_t r = 0; r < 1000; r++)
  {
    float p, q;
    isincos(r, &p, &q);
    sum += p + q;
  }
  stop = micros();
  Serial.print("ISINCOS: \t");
  Serial.print(stop - start);
  Serial.println(" us");
  Serial.println(sum, 4);
  delay(10);


  for (uint32_t r = 0; r < 100; r++)
  {
    float p, q, s, t;
    isincos(r * 0.1, &p, &q);
    s = isin(r * 0.1);
    t = icos(r * 0.1);
    if ((abs(p - s) > 0.0001) || (abs(q - t) > 0.0001))
    {
      Serial.print(r);
      Serial.print("\t");
      Serial.print(s, 6);
      Serial.print("\t");
      Serial.print(p, 6);
      Serial.print("\t");
      Serial.print(t, 6);
      Serial.print("\t");
      Serial.print(q, 6);
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
