//
//    FILE: weightPerformance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-17


#include "weight.h"

volatile float val, test;
float stone, lbs, ounce, kilo, kg;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("\nFUNCTION:\tTIME (us)");
  // measure_1();
  measure_2();
}


void loop()
{
}


void measure_1()
{
  test = random(20) * 0.12345;

  start = micros();
  for (int i = 0; i < 1000; i++) val = lbs2kilo(test);
  stop = micros();
  Serial.print("lbs2kilo:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = kilo2lbs(test);
  stop = micros();
  Serial.print("kilo2lbs:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = ounce2gram(test);
  stop = micros();
  Serial.print("ounce2gram:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = gram2ounce(test);
  stop = micros();
  Serial.print("gram2ounce:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = gram2kilo(test);
  stop = micros();
  Serial.print("gram2kilo:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = kilo2gram(test);
  stop = micros();
  Serial.print("kilo2gram:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = lbs2ounce(test);
  stop = micros();
  Serial.print("lbs2ounce:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = ounce2lbs(test);
  stop = micros();
  Serial.print("ounce2lbs:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = stone2lbs(test);
  stop = micros();
  Serial.print("stone2lbs:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = lbs2stone(test);
  stop = micros();
  Serial.print("lbs2stone:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = stone2kilo(test);
  stop = micros();
  Serial.print("stone2kilo:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = kilo2stone(test);
  stop = micros();
  Serial.print("kilo2stone:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);
}


void measure_2()
{
  test = random(20) * 0.12345;

  start = micros();
  for (int i = 0; i < 1000; i++) val = metric2US(test, stone, lbs, ounce);
  stop = micros();
  Serial.print("metric2US:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) val = US2metric(test, lbs, ounce);
  stop = micros();
  Serial.print("US2metric:\t");
  Serial.println((stop - start) * 0.001, 3);
  delay(100);

  Serial.println("\nDone...");
}


//  -- END OF FILE --

