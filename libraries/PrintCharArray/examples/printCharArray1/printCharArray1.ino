//
//    FILE: printCharArray1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PrintCharArray


#include "PrintCharArray.h"

PrintCharArray ps;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTCHARARRAY_VERSION: ");
  Serial.println(PRINTCHARARRAY_VERSION);
  Serial.println();

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


//  -- END OF FILE --
