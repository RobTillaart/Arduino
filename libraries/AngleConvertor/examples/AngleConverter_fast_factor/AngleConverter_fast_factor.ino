//
//    FILE: AngleConverter_fast_factor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angleConvertor class
//     URL: https://github.com/RobTillaart/AngleConvertor
//
//  if you need to convert a lot of data between two formats
//  it is faster if you precalculate a factor.
//  On an UNO R3 the gain is roughly 20%.


#include "AngleConvertor.h"

AngleConvertor conv;

uint32_t start, stop;
volatile float sum;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANGLECONVERTOR_LIB_VERSION: ");
  Serial.println(ANGLECONVERTOR_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    conv.setPechus(i);
    sum += conv.getAngularMil();
  }
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(sum);
  Serial.println();
  delay(100);

  //  precalculate the factor
  conv.setDegrees(1);  //  any non zero value will work.
  float factor = conv.getAngularMil() / conv.getPechus();
  //  do the test
  sum = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    sum += i * factor;
  }
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(sum);
  Serial.println();
  delay(100);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
