//
//    FILE: AngleConverter_windrose.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angleConvertor class
//    DATE: 2022-12-01
//     URL: https://github.com/RobTillaart/AngleConvertor
//


#include "AngleConvertor.h"

AngleConvertor conv;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("lib version: ");
  Serial.println(ANGLECONVERTOR_LIB_VERSION);
  Serial.println();


  for (int angle = 0; angle <= 360; angle += 5)
  {
    Serial.print(angle);
    Serial.print("\t");
    Serial.print(conv.windrose(angle));
    Serial.println();
  }
  Serial.println();
  delay(100);

  start = micros();
  conv.setDegrees(127.876);
  char * p = conv.windrose();
  stop = micros();

  Serial.print("WINDROSE TIME: \t");
  Serial.println(stop - start);
  Serial.print("WINDROSE  DIR: \t");
  Serial.println(p);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
