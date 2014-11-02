//
//    FILE: fastMapDemo2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo of FastMap class ==> a faster map function
//    DATE: 2014-11-02
//     URL:
//
// Released to the public domain
//

#include "FastMap.h"

FastMap CtoF;
FastMap FtoC;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start fastMapDemo2\nlib version: ");
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
//
// END OF FILE
//

