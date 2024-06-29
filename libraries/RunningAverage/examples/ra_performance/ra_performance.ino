//
//    FILE: ra_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-04-16
// PURPOSE: timing of runningAverage
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(50);
int samples = 0;

uint32_t start, stop;
volatile float x;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  Serial.println();

  myRA.clear();  //  explicitly start clean

  for (int i = 0; i < 10; i++)
  {
    myRA.addValue(random(1000) * 0.001);
  }

  test_clear();
  test_addvalue();

  test_fillValue();
  test_getValue();

  test_getAverage();
  test_getFastAverage();

  test_getStandardDeviation();
  test_getStandardError();

  test_getMin();
  test_getMax();
  test_getMinInBuffer();
  test_getMaxInBuffer();
  test_getSum();

  test_bufferIsFull();
  test_getElement();

  test_getSize();
  test_getCount();

  Serial.println("\ndone...\n");
}


void test_clear(void)
{
  start = micros();
  myRA.clear();
  stop = micros();
  Serial.print("\tclear \t\t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_addvalue()
{
  start = micros();
  myRA.addValue(3.1415);
  stop = micros();
  Serial.print("\taddValue \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_fillValue()
{
  start = micros();
  myRA.fillValue(1.235, 50);
  stop = micros();
  Serial.print("\tfillValue \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getValue()
{
  start = micros();
  x = myRA.getValue(4);
  stop = micros();
  Serial.print("\tgetValue \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getAverage()
{
  start = micros();
  x = myRA.getAverage();
  stop = micros();
  Serial.print("\tgetAverage \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getFastAverage()
{
  start = micros();
  x = myRA.getFastAverage();
  stop = micros();
  Serial.print("\tgetFastAverage \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getStandardDeviation()
{
  start = micros();
  x = myRA.getStandardDeviation();
  stop = micros();
  Serial.print("\tgetStandardDeviation \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getStandardError()
{
  start = micros();
  x = myRA.getStandardError();
  stop = micros();
  Serial.print("\tgetStandardError \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getMin()
{
  start = micros();
  x = myRA.getMin();
  stop = micros();
  Serial.print("\tgetMin \t\t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getMax()
{
  start = micros();
  x = myRA.getMax();
  stop = micros();
  Serial.print("\tgetMax \t\t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getMinInBuffer()
{
  start = micros();
  x = myRA.getMinInBuffer();
  stop = micros();
  Serial.print("\tgetMinInBuffer \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getMaxInBuffer()
{
  start = micros();
  x = myRA.getMaxInBuffer();
  stop = micros();
  Serial.print("\tgetMaxInBuffer \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getSum()
{
  start = micros();
  x = myRA.getSum();
  stop = micros();
  Serial.print("\tgetSum \t\t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_bufferIsFull()
{
  start = micros();
  x = myRA.bufferIsFull();
  stop = micros();
  Serial.print("\tbufferIsFull \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getElement()
{
  start = micros();
  x = myRA.getElement(4);
  stop = micros();
  Serial.print("\tgetElement \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getSize()
{
  start = micros();
  x = myRA.getSize();
  stop = micros();
  Serial.print("\tgetSize \t: ");
  Serial.println(stop - start);
  delay(10);
}


void test_getCount()
{
  start = micros();
  x = myRA.getCount();
  stop = micros();
  Serial.print("\tgetCount \t: ");
  Serial.println(stop - start);
  delay(10);
}


void loop()
{
}


//  -- END OF FILE --
