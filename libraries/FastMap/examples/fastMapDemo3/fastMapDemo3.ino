//    FILE: fastMapDemo3.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo of FastMap class ==> a faster map function
//    DATE: 2014-11-02
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// Released to the public domain
//

#include "FastMap.h"

FastMap CtoF;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start fastMapDemo3\nlib version: ");
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

  f = CtoF.map(163, CONSTRAIN_UPPER);
  Serial.print(f);
  Serial.print(char(176));
  Serial.println('F');

  c = CtoF.back(f, CONSTRAIN_BOTH);
  Serial.print(c);
  Serial.print(char(176));
  Serial.println('C');

}

void loop()
{
}
//
// END OF FILE
//

