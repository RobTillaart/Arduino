//
//    FILE: functionGeneratorPerformance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo function generators
//    DATE: 2015-01-01
//     URL: https://github.com/RobTillaart/FunctionGenerator


#include "functionGenerator.h"

uint32_t start;
uint32_t stop;

volatile float t;
volatile float y;

funcgen gen;


//  sin(t) + 0.25 * sin(5t)
int16_t arr_two_sin[101] =
{
  0, 1120, 2178, 3117, 3891, 4472,
  4847, 5024, 5029, 4904, 4702,
  4481, 4300, 4213, 4261, 4472,
  4852, 5392, 6063, 6820, 7608,
  8366, 9033, 9554, 9886, 10000,
  9886, 9554, 9033, 8366, 7608,
  6820, 6063, 5392, 4852, 4472,
  4261, 4213, 4300, 4481, 4702,
  4904, 5029, 5024, 4847, 4472,
  3891, 3117, 2178, 1120, 0,
  -1120, -2178, -3117, -3891, -4472,
  -4847, -5024, -5029, -4904, -4702,
  -4481, -4300, -4213, -4261, -4472,
  -4852, -5392, -6063, -6820, -7608,
  -8366, -9033, -9554, -9886, -10000,
  -9886, -9554, -9033, -8366, -7608,
  -6820, -6063, -5392, -4852, -4472,
  -4261, -4213, -4300, -4481, -4702,
  -4904, -5029, -5024, -4847, -4472,
  -3891, -3117, -2178, -1120, 0,
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FUNCTIONGENERATOR_LIB_VERSION: ");
  Serial.println(FUNCTIONGENERATOR_LIB_VERSION);
  Serial.println();

  Serial.println("func \t\tusec\tmax calls/sec  (indicative)");
  y = analogRead(A0) / 1024;
  test_square();
  delay(10);
  test_sawtooth();
  delay(10);
  test_triangle();
  delay(10);
  test_sinus();
  delay(10);
  test_stair();
  delay(10);
  test_random();
  delay(10);
  test_random_DC();
  delay(10);
  test_line();
  delay(10);
  test_zero();
  delay(10);
  test_sinusDiode();
  delay(10);
  test_sinusRectified();
  delay(10);
  test_trapezium1();
  delay(10);
  test_trapezium2();
  delay(10);
  test_heartBeat();
  delay(10);
  test_freeWave();
  delay(10);
  Serial.println();

  Serial.println("t \t sqr\t saw\t tri\t sin\t str\t rnd\t line\t zero\t sinD\t sinR\t trap");
  for (int i = -400; i < 400; i += 2)
  {
    float t = i * 0.01;
    Serial.print(t);
    Serial.print("\t");
    Serial.print(gen.square(t));
    Serial.print("\t");
    Serial.print(gen.sawtooth(t));
    Serial.print("\t");
    Serial.print(gen.triangle(t));
    Serial.print("\t");
    Serial.print(gen.sinus(t));
    Serial.print("\t");
    Serial.print(gen.stair(t));
    Serial.print("\t");
    Serial.print(gen.random());
    Serial.print("\t");
    Serial.print(gen.line());
    Serial.print("\t");
    Serial.print(gen.zero());
    Serial.print("\t");
    Serial.print(gen.sinusDiode(t));
    Serial.print("\t");
    Serial.print(gen.sinusRectified(t));
    Serial.print("\t");
    Serial.print(gen.trapezium2(t));
    Serial.println();
  }
  Serial.println("\ndone...");
}


/******************************************************************/

void test_square()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.square(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_sawtooth()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.sawtooth(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_triangle()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.triangle(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_sinus()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.sinus(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_stair()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.stair(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_random()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.random();
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_random_DC()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.random_DC();
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_line()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.line();
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_zero()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.zero();
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_sinusDiode()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.sinusDiode(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_sinusRectified()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.sinusRectified(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_trapezium1()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.trapezium1(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_trapezium2()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.trapezium2(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_heartBeat()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.heartBeat(i);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void test_freeWave()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = gen.freeWave(i, arr_two_sin, 100);
  }
  stop = micros();
  Serial.print(__FUNCTION__);
  Serial.print(":\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}


void loop()
{
}


//  -- END OF FILE --
