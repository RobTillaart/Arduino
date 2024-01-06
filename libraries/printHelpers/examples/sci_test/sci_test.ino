//
//    FILE: sci_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test different values with sci function
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  test1();
  test2();
  test3();
  test4();
  test5();
  test6();

  Serial.println("\nDone...");
}


void loop()
{
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  double f = 1;
  for (int i = 0; i < 40; i++)
  {
    f *= 10;
    Serial.println(sci(f, 6));
  }
  Serial.println();

  f = 1;
  for (int i = 0; i < 50; i++)
  {
    f /= 10;
    Serial.println(sci(f, 6));
  }
  Serial.println();

  f = -1;
  for (int i = 0; i < 40; i++)
  {
    f *= 10;
    Serial.println(sci(f, 6));
  }
  Serial.println();

  f = -1;
  for (int i = 0; i < 50; i++)
  {
    f /= 10;
    Serial.println(sci(f, 6));
  }
  Serial.println();
  Serial.println();
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  double f = 1;
  for (int i = 0; i < 40; i++)
  {
    f *= (PI * PI);
    Serial.println(sci(f, 6));
  }
  Serial.println();
  f = 1;
  for (int i = 0; i < 50; i++)
  {
    f /= (PI * PI);
    Serial.println(sci(f, 6));
  }
  Serial.println();
  f = -1;
  for (int i = 0; i < 40; i++)
  {
    f *= (PI * PI);
    Serial.println(sci(f, 6));
  }
  Serial.println();
  f = -1;
  for (int i = 0; i < 50; i++)
  {
    f /= (PI * PI);
    Serial.println(sci(f, 6));
  }
  Serial.println();
  Serial.println();
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  double f = PI;
  for (int digits = 0; digits < 15; digits++)
  {
    Serial.println(sci(f, digits));
  }
  Serial.println();
}


void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  double f = PI;
  for (int digits = 0; digits < 15; digits++)
  {
    sci(Serial, f, digits);
    Serial.println();
  }
  Serial.println();
}


void test5()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  double f = 1.0 / 0.0;
  Serial.println(sci(f, 6));
  f = 0.0 / 0.0;
  Serial.println(sci(f, 6));
  f = -1.0 / 0.0;
  Serial.println(sci(f, 6));
  // TODO find a -inf
  Serial.println(sci(tan(PI / 2), 6));
  Serial.println();
}


void test6()
{
  if (sizeof(double) >= 8)
  {
    Serial.println("DEC\tTIME\tVALUE");
    for (int i = 0; i < 16; i++)
    {
      double f = PI * 1E307;  // causes warning...
      start = micros();
      char * b = sci(f, i);
      stop = micros();
      Serial.print(i);
      Serial.print('\t');
      Serial.print(stop - start);
      Serial.print('\t');
      Serial.print(b);
      Serial.println();
      delay(10);
    }
    Serial.println();
  }

  // floats
  Serial.println("DEC\tTIME\tVALUE");
  for (int i = 0; i < 16; i++)
  {
    double f = PI * 1E38;
    start = micros();
    char * b = sci(f, i);
    stop = micros();
    Serial.print(i);
    Serial.print('\t');
    Serial.print(stop - start);
    Serial.print('\t');
    Serial.print(b);
    Serial.println();
    delay(10);
  }
}


//  -- END OF FILE --

