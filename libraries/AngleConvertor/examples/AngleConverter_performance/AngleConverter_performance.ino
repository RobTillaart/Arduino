//
//    FILE: AngleConverter_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angleConvertor class
//     URL: https://github.com/RobTillaart/AngleConvertor


#include "AngleConvertor.h"

AngleConvertor conv;

uint32_t start, stop;
volatile float x;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANGLECONVERTOR_LIB_VERSION: ");
  Serial.println(ANGLECONVERTOR_LIB_VERSION);
  Serial.println();
  delay(10);

  start = micros();
  conv.setDegrees(1.2345);
  x = conv.getTurn();
  stop = micros();

  Serial.print("TIME: \t");
  Serial.println(stop - start);  //  2 steps

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
