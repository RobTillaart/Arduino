//
//    FILE: polynome.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: polynome test
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
float x, y, z, sum, error;
float YY1, YY2, YY3;
float ar[3];


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(1000);

  sum = 0;
  start = micros();
  for (x = 0; x < 10; x++)
  {
    sum += polynome(x, ar, 2);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\n");
  delay(100);

  //  ax^2 + bx + c == 42 for x = 10.
  //  ax^2 + bx + c == 3 for x = 5.
  //  ax^2 + bx + c == 3 for x = 3.
  Serial.println("\nFind the minimum a,b,c");

  search_heat();
  Serial.println();
  //  search_linear();  //  takes forever

  Serial.println("done...");
}


void loop()
{
}


//  brute force search takes forever
void search_linear()
{
  float minimum = 1000000000;
  uint32_t start = millis();
  for (float c = -20; c <= 20; c += 0.1)
  {
    for (float b = -20; b <= 20; b += 0.1)
    {
      for (float a = -20; a <= 20; a += 0.1)
      {
        ar[0] = a;
        ar[1] = b;
        ar[2] = c;
        YY1 = polynome(10, ar, 2);
        YY2 = polynome(5, ar, 2);
        YY3 = polynome(3, ar, 2);
        error = 0;
        error += (YY1 - 42) * (YY1 - 42);
        error += (YY2 -  3) * (YY2 -  3);
        error += (YY3 -  3) * (YY3 -  3);
        if (error < minimum)
        {
          minimum = error;
          Serial.print(millis() - start);
          Serial.print("\t");
          Serial.print(a);
          Serial.print("\t");
          Serial.print(b);
          Serial.print("\t");
          Serial.print(c);
          Serial.print("\t");
          Serial.print(YY1, 3);
          Serial.print("\t");
          Serial.print(YY2, 3);
          Serial.print("\t");
          Serial.print(YY3, 3);
          Serial.print("\t");
          Serial.print(error, 6);
          Serial.print("\n");
        }
      }
    }
  }
}


//  search and improve stepwise goes way faster
void search_heat()
{
  float error;
  float minimum = 1E9;
  float a, b, c;
  a = b = c = 0;  //  arbitrary start
  uint32_t start = millis();
  while (millis() - start < 60000)  //  search for 1 minute
  {
    //  look random around for a better fit
    ar[0] = a - 0.5 + random(10000) * 0.0001;
    ar[1] = b - 0.5 + random(10000) * 0.0001;
    ar[2] = c - 0.5 + random(10000) * 0.0001;

    // calculate the points.
    YY1 = polynome(10, ar, 2);
    YY2 = polynome(5, ar, 2);
    YY3 = polynome(3, ar, 2);

    // determine error squared
    error = 0;
    error += (YY1 - 42) * (YY1 - 42);
    error += (YY2 -  3) * (YY2 -  3);
    error += (YY3 -  3) * (YY3 -  3);
    
    //  if new values is a better fit
    if (error < minimum)
    {
      //  remember the new values
      minimum = error;
      a = ar[0];
      b = ar[1];
      c = ar[2];
      // output them.
      Serial.print(millis() - start);
      Serial.print("\t");
      Serial.print(ar[0], 2);
      Serial.print("\t");
      Serial.print(ar[1], 2);
      Serial.print("\t");
      Serial.print(ar[2], 2);
      Serial.print("\t");
      Serial.print(YY1, 3);
      Serial.print("\t");
      Serial.print(YY2, 3);
      Serial.print("\t");
      Serial.print(YY3, 3);
      Serial.print("\t");
      Serial.print(error, 6);
      Serial.print("\n");
    }
  }
}


//  -- END OF FILE --
