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


void setup()
{
  Serial.begin(115200);
  Serial.print("Start functionGeneratorPerformance - LIB VERSION: ");
  Serial.println(FUNCTIONGENERATOR_LIB_VERSION);

  Serial.println("func \t\tusec\tmax calls/sec");
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
  Serial.println();

  Serial.println("t \t sqr\t saw\t tri\t sin\t str\t rnd\t line\t zero");
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


void loop()
{
}


//  -- END OF FILE --

