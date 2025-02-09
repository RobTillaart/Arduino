//
//    FILE: OUTPIN_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: get some performance figures
//     URL: https://github.com/RobTillaart/OUTPIN


#include "OUTPIN.h"

//  adjust pin if needed
OUTPIN op(13, LOW);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("OUTPIN_LIB_VERSION: ");
  Serial.println(OUTPIN_LIB_VERSION);
  Serial.println();
  delay(100);

  test_set_high_low();
  test_pulseHigh();
  test_pulseOut();
}


void loop()
{
}


void test_set_high_low()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(13, HIGH);
  }
  stop = micros();
  Serial.print("DW:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.set(HIGH);
  }
  stop = micros();
  Serial.print("set:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.high();
  }
  stop = micros();
  Serial.print("high:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.low();
  }
  stop = micros();
  Serial.print("low:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.toggle();
  }
  stop = micros();
  Serial.print("toggle:\t");
  Serial.println(stop - start);
  delay(100);
}


void test_pulseHigh()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(13, HIGH);
    digitalWrite(13, LOW);
  }
  stop = micros();
  Serial.print("DW:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.pulseHigh();
  }
  stop = micros();
  Serial.print("pulseHigh():\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.pulseHigh(0);
  }
  stop = micros();
  Serial.print("pulseHigh(0):\t");
  Serial.println(stop - start);
  int x = stop - start;
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.pulseHigh(20);
  }
  stop = micros();
  Serial.print("pulseHigh(20):\t");
  Serial.println(stop - start);
  Serial.print("step size:\t");
  Serial.println((stop - start - x) * 0.00005, 4);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    op.pulseHigh(13);
  }
  stop = micros();
  Serial.print("pulseHigh(13):\t");
  Serial.println(stop - start);
  delay(100);
}

void test_pulseOut()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(100);

  for (int del = 10; del <= 100; del += 10)
  {
    start = micros();
    op.pulseOut(LOW, del);
    stop = micros();
    Serial.print("pulseOut:\t");
    Serial.print(del);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(100);
  }

  for (int del = 100; del <= 1000; del += 100)
  {
    start = micros();
    op.pulseOut(LOW, del);
    stop = micros();
    Serial.print("pulseOut:\t");
    Serial.print(del);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(100);
  }

  for (int del = 1000; del <= 10000; del += 1000)
  {
    start = micros();
    op.pulseOut(LOW, del);
    stop = micros();
    Serial.print("pulseOut:\t");
    Serial.print(del);
    Serial.print("\t");
    Serial.println(stop - start);
    delay(100);
  }
}

//  -- END OF FILE --
