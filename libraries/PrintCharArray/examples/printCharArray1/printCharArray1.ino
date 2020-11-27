//
//    FILE: printCharArray1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PrintCharArray
//
// HISTORY:
// 0.1.0 2017-12-07 initial version
//

#include "PrintCharArray.h"

PrintCharArray ps;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println(ps.free());
  ps.println("Hello World");
  Serial.println(ps.free());
  ps.println(3.14159265, 4);
  Serial.println(ps.free());
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
