//
//    FILE: AngleConverter_adder.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch
//     URL: https://github.com/RobTillaart/AngleConvertor
//


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
    conv.addRadians(i);
  }
  stop = micros();
  sum = conv.getDegrees();
  Serial.println("convert radians and add");
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(sum);
  Serial.println();
  delay(100);

  sum = 0;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    sum += i;
  }
  conv.setRadians(sum);
  stop = micros();
  sum = conv.getDegrees();
  Serial.println("add radians and convert once");
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
