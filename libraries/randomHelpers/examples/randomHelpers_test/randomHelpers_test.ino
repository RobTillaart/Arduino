//
//    FILE: randomHelpers_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/randomHelpers


#include "randomHelpers.h"

uint32_t start, stop, duration1, duration2;

volatile uint32_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("RANDOM_HELPERS_VERSION: ");
  Serial.println(RANDOM_HELPERS_VERSION);
  Serial.println();
  
  test_getRandom1();
  test_getRandom6();
  test_getRandom8();
  test_getRandom16();
  test_getRandom24();
  test_getRandom32();
  test_throwDice();
}


void loop()
{
}


void test_getRandom1()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(2);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom1();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_getRandom6()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(32);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom6();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_getRandom8()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(256);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom8();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_getRandom16()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(65536);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom16();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_getRandom24()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(16777216);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom24();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_getRandom32()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(0xFFFFFFFF);
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = getRandom32();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_throwDice()
{
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = random(6) + 1;
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = throwDice();
  }
  duration2 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME 1:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("TIME 2:\t");
  Serial.print(duration2);
  Serial.println();
  Serial.print("RATIO :\t");
  Serial.print((1.0 * duration1) / duration2);
  Serial.println();
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
