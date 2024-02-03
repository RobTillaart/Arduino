//
//    FILE: map2bits_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2bits demo
//     URL: https://github.com/RobTillaart/map2bits


#include "map2bits.h"

map2bits mb;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2BITS_LIB_VERSION: ");
  Serial.println(MAP2BITS_LIB_VERSION);
  Serial.println();

  mb.init(100, 200, 10);
  for (int i = 0; i < 300; i += 10)
  {
    Serial.println(mb.map(i), BIN);
  }
  Serial.println();

  mb.init(100, 1000, 32);
  for (int i = 0; i <= 1000; i += 1)
  {
    Serial.println(mb.map(i), BIN);
  }
  Serial.println();

  Serial.println("Done...");
}


void loop()
{

}


// -- END OF FILE --
