//
//    FILE: map2bits_analogRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2bits demo
//     URL: https://github.com/RobTillaart/map2bits


#include "map2bits.h"

map2bits mb;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAP2BITS_LIB_VERSION: ");
  Serial.println(MAP2BITS_LIB_VERSION);
  Serial.println();

  mb.init(0, 1023, 16);
}


void loop()
{
  Serial.println(mb.map(analogRead(A0)), BIN);
  delay(50);
}


// -- END OF FILE --
