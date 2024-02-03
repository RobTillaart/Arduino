//    FILE: fastMapDemo3.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of FastMap class ==> a faster map function
//     URL: https://github.com/RobTillaart/FastMap
//          http://forum.arduino.cc/index.php?topic=276194


#include "FastMap.h"

FastMap CtoF;  //  Celsius to Fahrenheit


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FASTMAP_LIB_VERSION: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  CtoF.init(0, 100, 32, 212);

  float f = CtoF.map(163);
  Serial.print(f);
  Serial.print(char(176));
  Serial.println('F');

  float c = CtoF.back(f);
  Serial.print(c);
  Serial.print(char(176));
  Serial.println('C');

  f = CtoF.upperConstrainedMap(163);
  Serial.print(f);
  Serial.print(char(176));
  Serial.println('F');

  f = CtoF.lowerConstrainedMap(163);
  Serial.print(f);
  Serial.print(char(176));
  Serial.println('C');
}

void loop()
{
}


//  -- END OF FILE --
