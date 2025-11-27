//
//    FILE: map2bits_random.ino
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

  if (mb.init(0, 1000, 32) == false)
  {
    Serial.println("init failed.");
  }
}


void loop()
{
  Serial.println(mb.map32(random(1000)), BIN);
  delay(25);
}


// -- END OF FILE --
