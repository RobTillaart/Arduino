//
//    FILE: runningAngle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demonstrates the usage of the runningAngle Class


#include "runningAngle.h"


uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test0();
  test1();
  test2();
  test3();
}


void loop()
{
}


void test0()
{
  runningAngle heading(runningAngle::DEGREES);

  Serial.println("\nTIMING ADD 0..360");
  delay(10);
  heading.reset();
  start = micros();
  for (int i = 0; i < 360; i++)
  {
    heading.add(i);
  }
  stop = micros();
  Serial.println(stop - start);
  delay(10);

  Serial.println("\nTIMING ADD 360..720 (more wrapping)");
  delay(10);
  heading.reset();
  start = micros();
  for (int i = 360; i < 720; i++)
  {
    heading.add(i);
  }
  stop = micros();
  Serial.println(stop - start);
  delay(10);

  Serial.println();
  delay(10);
}


void test1()
{
  Serial.println("\nADD 0 .. 360");
  runningAngle heading(runningAngle::DEGREES);
  heading.reset();
  for (int i = 0; i < 360; i++)heading.add(i);
  Serial.println(heading.getAverage());
  heading.reset();
  for (int i = 360; i > 0; i--) heading.add(i);
  Serial.println(heading.getAverage());
  Serial.println();
  delay(10);
}


// shows effect of weight
// e.g. to a robot rotating 360 degrees
void test2()
{
  Serial.println("\nTEST WEIGHTS");

  runningAngle heading(runningAngle::DEGREES);
  for (int f = 0; f <= 100; f++)
  {
    Serial.print(f * 0.01, 2);
    Serial.print("\t");
    heading.reset();
    heading.setWeight(f * 0.01);
    for (int i = 0; i <= 360; i++) heading.add(i);
    Serial.print(heading.getAverage());
    Serial.print("\t");
    Serial.print("\n");
  }

  Serial.println();
  delay(10);
}


void test3()
{
  Serial.println("\nTEST 100x ADD 10000 RANDOM ANGLES");

  runningAngle heading(runningAngle::DEGREES);
  for (int f = 0; f <= 100; f++)
  {
    Serial.print(f);
    Serial.print("\t");
    heading.reset();
    for (int i = 0; i <= 10000; i++) heading.add(random(360));
    Serial.print(heading.getAverage());
    Serial.print("\n");
  }

  Serial.println();
  delay(10);
}


//  -- END OF FILE --

