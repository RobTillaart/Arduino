//
//    FILE: AngleConverter_fast_factor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angleConvertor class
//     URL: https://github.com/RobTillaart/AngleConvertor
//
//  if you need to convert a lot of data between two formats
//  it is faster if you pre calculate a factor.
//  On an UNO R3 the gain is roughly 20%.


#include "AngleConvertor.h"

AngleConvertor conv;

uint32_t start, stop, d1, d2;
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
  d2 = stop - start;
  Serial.print("Two step conversion time: \t");
  Serial.println(d2);
  Serial.println(sum);
  Serial.println();
  delay(100);

  //  pre calculate the factor
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
  d1 = stop - start;
  Serial.print("One step conversion time: \t");
  Serial.println(d1);
  Serial.println(sum);
  Serial.println();
  delay(100);

  Serial.print("Faster: \t");
  Serial.print(100.0 - (100.0 * d1) / d2, 2);
  Serial.println("%");
  Serial.println();
  delay(100);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
