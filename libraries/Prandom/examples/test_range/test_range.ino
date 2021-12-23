//
//    FILE: test_range.ino
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
  Serial.println();

  Serial.println(F("TIME\tSUM\t\tSSQ\t\tMIN\tMAX\t\tFunction"));
  for (int i = 0; i < 70; i++) Serial.print('=');
  Serial.println();

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
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.randrange(100);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
}


void test_randrange_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.randrange(100, 200);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_randrange_3()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.randrange(100, 200, 5);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_random_0()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.random();
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_random_1()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.random(4);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_uniform_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.uniform(EULER, PI);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_triangular_0()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.triangular(0, 10, 3);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_normalvariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.normalvariate(5, 1);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_lognormvariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.lognormvariate(5, 1);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_gauss_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.gauss(5, 1);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_expovariate_1()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.expovariate(1.0 / 5);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_gammavariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.gammavariate(200, 1);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_betavariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.betavariate(3, 3);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_paretovariate_1()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.paretovariate(10);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_weibullvariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.weibullvariate(PI, 1);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


void test_vonmisesvariate_2()
{
  float sum = 0;
  float sqsum = 0;
  float _min = 1e20;
  float _max = -1e20;
  start = micros();
  for (int i = 0; i < runs; i++)
  {
    float x = R.vonmisesvariate(PI / 2, 0);
    if (x < _min) _min = x;
    if (x > _max) _max = x;
    sum += x;
    sqsum += x * x;
  }
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(sqsum);
  Serial.print("\t");
  Serial.print(_min);
  Serial.print("\t");
  Serial.print(_max);
  Serial.print("\t\t");
  Serial.println(__FUNCTION__);
}


// -- END OF FILE --

