//
//    FILE: functionGeneratorPerformance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo function generators
//    DATE: 2015-01-01
//     URL:
//
// Released to the public domain
//

#include "functionGenerator.h"

uint32_t start;
uint32_t stop;

volatile double t;
volatile double y;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start functionGeneratorPerformance - LIB VERSION: ");
  Serial.println(FUNCTIONGENERATOR_LIB_VERSION);
  
  Serial.println("func \t usec\t max calls/sec");
  y = analogRead(A0) / 1024;
  test_fgsqr();
  delay(10);
  test_fgsaw();
  delay(10);
  test_fgtri();
  delay(10);
  test_fgsin();
  delay(10);
  test_fgstr();
  delay(10);
  Serial.println();

  Serial.println("t \t sqr\t saw\t tri\t sin\t str");
  for (int i = -400; i < 400; i += 2)
  {
    // func(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0)
    double t = i * 0.01;
    Serial.print(t);
    Serial.print("\t");
    Serial.print(fgsqr(t));
    Serial.print("\t");
    Serial.print(fgsaw(t));  //, 2.0, 1.0, 0.5));
    Serial.print("\t");
    Serial.print(fgtri(t));  //, 1.0, 0.5, 1.0));
    Serial.print("\t");
    Serial.print(fgsin(t));  // , TWO_PI, 1.0, PI / 4)); // period 2PI, phase = 45°
    // Serial.print(fgsin(t, 1.0, 0.5, -0.5, 0.5));
    Serial.print("\t");
    Serial.print(fgstr(t));
    Serial.println();
  }
  Serial.println("\ndone...");
}


/******************************************************************/

void test_fgsqr()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = fgsqr(i);
  }
  stop = micros();
  Serial.print("fsqr:\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}

void test_fgsaw()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = fgsaw(i);
  }
  stop = micros();
  Serial.print("fsaw:\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}

void test_fgtri()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = fgtri(i);
  }
  stop = micros();
  Serial.print("ftri:\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}

void test_fgsin()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = fgsin(i);
  }
  stop = micros();
  Serial.print("fsin:\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}

void test_fgstr()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    t = fgstr(i);
  }
  stop = micros();
  Serial.print("fstr:\t");
  Serial.print((stop - start) / 10000.0);
  Serial.print("\t");
  Serial.println(1000000.0 / ((stop - start) / 10000.0));
}

void loop()
{
}

// END OF FILE