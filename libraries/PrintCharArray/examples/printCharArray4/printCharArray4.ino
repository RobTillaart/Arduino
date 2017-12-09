//
//    FILE: printCharArray4.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo it takes less time to send data out.
//
// HISTORY:
// 0.1.0 2017-12-09 initial version
//

#include "PrintCharArray.h"

PrintCharArray ps;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println("Using direct print");
  start = millis();
  for (int i=0; i<10; i++)
  {
    Serial.println(1000+i);
  }
  stop = millis();
  Serial.println(stop - start);
  Serial.println();

  Serial.println("Using printCharArray");
  ps.clear();
  for (int i=0; i<10; i++)
  {
    ps.println(1000+i)
  }
  start = millis();
  Serial.println(ps.getBuffer());
  stop = millis();
  Serial.println(stop - start);
  Serial.println();

  Serial.println(ps.getBuffer());
  Serial.println(ps.free());

}

void loop()
{

}

