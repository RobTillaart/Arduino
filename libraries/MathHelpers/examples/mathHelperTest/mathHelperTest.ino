//
//    FILE: mathHelperTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE:
//
// HISTORY:

#include "MathHelpers.h"

uint32_t start;
uint32_t stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATHHELPERS_VERSION: ");
  Serial.println(MATHHELPERS_VERSION);

  test1();
  test2();
  test3();
  test4();
  test5();

  test10();
  test11();
  test12();

}

void loop()
{}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  float f = 1;
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

  float f = 1;
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

  float f = PI;
  for (int i = 0; i < 8; i++)
  {
    Serial.println(sci(f, i));
  }
  Serial.println();
}

void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  float f = PI;
  for (int i = 0; i < 8; i++)
  {
    sci(Serial, f, i);
    Serial.println();
  }
  Serial.println();
}


void test5()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  float f = 1.0 / 0.0;
  Serial.println(sci(f, 6));
  f = 0.0 / 0.0;
  Serial.println(sci(f, 6));
  f = -1.0 / 0.0;
  Serial.println(sci(f, 6));
  // TODO find a -inf

  Serial.println();
}


void test10()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.println("HH:MM:SS");
  for (int i = 0; i < 7; i++)
  {
    uint32_t now = micros();
    Serial.println(seconds2clock(now));
  }
  Serial.println();
}

void test11()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.println("HH:MM:SS.nnn");
  for (int i = 0; i < 7; i++)
  {
    uint32_t now = micros();
    Serial.println(millis2clock(now));
  }
  Serial.println();
}

void test12()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.println("time\tweeks\tdays\thours\tminutes");
  for (int i = 0; i < 7; i++)
  {
    uint32_t now = micros();
    Serial.print(now);
    Serial.print('\t');
    Serial.print(weeks(now), 3);
    Serial.print('\t');
    Serial.print(days(now), 3);
    Serial.print('\t');
    Serial.print(hours(now), 2);
    Serial.print('\t');
    Serial.println(minutes(now), 2);
  }
  Serial.println();
}


// END OF FILE
