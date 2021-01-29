//
//    FILE: printCharArray1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PrintCharArray
//
//  HISTORY:
//  0.1.0   2017-12-07  initial version
//  0.3.0   2021-01-06  free() => available()

#include "PrintCharArray.h"

PrintCharArray ps;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println(ps.available());
  ps.println("Hello World");
  Serial.println(ps.available());
  ps.println(3.14159265, 4);
  Serial.println(ps.available());
  Serial.println(ps.getBuffer());

  ps.clear();
  ps.println(3.14159265, 4);
  ps.println("Hello World");
  Serial.println(ps.getBuffer());
}

void loop()
{

}

// -- END OF FILE --
