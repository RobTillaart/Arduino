//
//    FILE: IEEE754_equal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: experimental
//     URL: https://github.com/RobTillaart/IEEE754tools
//
//  Notes
//  - Works on AVR
//  - Fails on ESP32


#include "IEEE754tools.h"


uint32_t start, duration;
volatile bool b;


void test_FLOAT_EQ_1()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  float f = PI;
  float g = PI;

  Serial.print("IEEE_FLOAT_EQ : ");
  Serial.println(IEEE_FLOAT_EQ(f, g));
  Serial.print("IEEE_FLOAT_NEQ: ");
  Serial.println(IEEE_FLOAT_NEQ(f, g));

  f += 1;
  Serial.print("IEEE_FLOAT_EQ : ");
  Serial.println(IEEE_FLOAT_EQ(f, g));
  Serial.print("IEEE_FLOAT_NEQ: ");
  Serial.println(IEEE_FLOAT_NEQ(f, g));

  Serial.println();
}


void test_FLOAT_EQ_2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  float f = PI;
  float g = PI;
  start = micros();
  b = (f == g);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  delay(10);

  start = micros();
  b = IEEE_FLOAT_EQ(f, g);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  delay(10);

  g += 1;
  start = micros();
  b = (f == g);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  delay(10);

  start = micros();
  b = IEEE_FLOAT_EQ(f, g);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);

  Serial.println();
}


void test_DIV2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  volatile float f = random(1000) * 0.01;
  Serial.print("VALUE: ");
  Serial.println(f, 10);
  delay(10);

  start = micros();
  float g = f / 2;
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(f, 10);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  start = micros();
  g = IEEE_FLOAT_DIV2(f);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(f, 10);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  start = micros();
  g = IEEE_FLOAT_POW2fast(f, -1);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(f, 10);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  Serial.println();
}


void test_POW2()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  int p = random(10);
  float f = random(1000) * 0.001;
  Serial.println(f, 10);
  delay(10);

  start = micros();
  float g = f * pow(2, p);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  start = micros();
  g = IEEE_POW2(f, p);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  start = micros();
  g = IEEE_FLOAT_POW2fast(f, p);
  duration = micros() - start;
  Serial.print("TIME : ");
  Serial.println(duration);
  Serial.print("VALUE: ");
  Serial.println(g, 10);
  delay(10);

  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("IEEE754_LIB_VERSION: ");
  Serial.println(IEEE754_LIB_VERSION);
  Serial.println();

  test_FLOAT_EQ_1();
  test_FLOAT_EQ_2();
  test_DIV2();
  test_POW2();

  Serial.println("done");
}


void loop()
{
}


//  -- END OF FILE --

