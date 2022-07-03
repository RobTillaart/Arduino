//
//    FILE: DEVRANDOM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-23
//

// USE WITH SERIAL PLOTTER


#include "DEVRANDOM.h"

DEVRANDOM dr;

volatile int a, b, c, d;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("SOFTWARE\tDIGITAL\tANALOG\tMARSAGLIA");
}


void loop()
{
  dr.useRandom();
  a = dr.read();
  a = dr.read();
  dr.useDigitalRead(4);
  b = dr.read();
  b = dr.read();
  dr.useAnalogRead(A0);
  c = dr.read();
  c = dr.read();
  dr.useMarsaglia();
  d = dr.read();
  d = dr.read();

  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print(d);
  Serial.println();
}


// -- END OF FILE --

