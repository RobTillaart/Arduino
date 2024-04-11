//    FILE: CRC_include_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test namespaces
//     URL: https://github.com/RobTillaart/CRC


#include "Arduino.h"
#include "foo.h"
#include "CrcFastReverse.h"


void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);

  int x = reverse8bits(0xAA);
  Serial.println(x, HEX);
  Serial.println(millis());
  
  int y = foo(0xAA);
  Serial.println(y, HEX);
}

void loop()
{
}


//  -- END OF FILE --
