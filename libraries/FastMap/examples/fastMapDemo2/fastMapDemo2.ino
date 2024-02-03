//
//    FILE: fastMapDemo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of FastMap class ==> a faster map function
//     URL: https://github.com/RobTillaart/FastMap


#include "FastMap.h"

FastMap CtoF;  //  Celsius to Fahrenheit
FastMap FtoC;  //  Fahrenheit to Celsius


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FASTMAP_LIB_VERSION: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  CtoF.init(0, 100, 32, 212);
  FtoC.init(32, 212, 0, 100);

  float f = FtoC.map(163);
  Serial.print(f);
  Serial.print(char(223));
  Serial.println('C');

  float c = CtoF.map(f);
  Serial.print(c);
  Serial.print(char(223));
  Serial.println('F');
}


void loop()
{
}


//  -- END OF FILE --

