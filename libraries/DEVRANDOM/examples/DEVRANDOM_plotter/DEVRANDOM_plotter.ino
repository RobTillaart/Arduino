//
//    FILE: DEVRANDOM_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-23
//    (c) : MIT
//

// USE WITH SERIAL PLOTTER

#include "DEVRANDOM.h"

DEVRANDOM dr;

volatile int x, y, z;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("SOFTWARE\tDIGITAL\tANALOG");
}

void loop()
{
  dr.useSW();
  x = dr.read();
  dr.useHW(4);
  x = dr.read();
  dr.useAR(A0);
  x = dr.read();

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.println();
}

// -- END OF FILE --
