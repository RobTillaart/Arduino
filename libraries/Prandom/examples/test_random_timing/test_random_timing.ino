//
//    FILE: test_random_timing.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-05-13


#include "Prandom.h"

const int runs = 1000;

Prandom R;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println(F("TIME\tSUM\t\tFunction"));
  Serial.println(F("========================================"));

  test_randrange_1();
  test_randrange_2();
  test_randrange_3();
  Serial.println();

  test_random_0();
  test_random_1();
  test_uniform_2();
  test_triangular_0();
  test_normalvariate_2();
  test_lognormvariate_2();
  test_gauss_2();
  test_expovariate_1();
  test_gammavariate_2();
  test_betavariate_2();
  test_paretovariate_1();
  test_weibullvariate_2();
  test_vonmisesvariate_2();

  Serial.println("\nDone...");
}


void loop() {}


void test_randrange_1()
{
  uint32_t sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.randrange(0x000FFFFF);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_randrange_2()
{
  uint32_t sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.randrange(1000, 2000);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_randrange_3()
{
  uint32_t sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.randrange(1000, 2000, 5);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_random_0()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.random();
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_random_1()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.random(4);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_uniform_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.uniform(EULER, PI);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_triangular_0()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.triangular(EULER, PI, 3);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_normalvariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.normalvariate(5, 1);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_lognormvariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.lognormvariate(5, 1);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_gauss_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.gauss(5, 1);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_expovariate_1()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.expovariate(0.15);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_gammavariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.gammavariate(200, 1);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_betavariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.betavariate(3, 3);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_paretovariate_1()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.paretovariate(10);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_weibullvariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.weibullvariate(PI, 1);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_vonmisesvariate_2()
{
  float sum = 0;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    sum += R.vonmisesvariate(PI / 2, 0);
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


// -- END OF FILE --

