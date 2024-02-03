//
//    FILE: map2bits_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2bits demo
//     URL: https://github.com/RobTillaart/map2bits


#include "map2bits.h"

map2bits mb;
map2bits mb2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2BITS_LIB_VERSION: ");
  Serial.println(MAP2BITS_LIB_VERSION);
  Serial.println();

  mb.init(100, 1000, 32);
  mb2.init(0, 100, 32);
  for (int i = 0; i <= 1000; i += 2)
  {
    Serial.print(mb.map(i), DEC);
    Serial.print("\t");
    Serial.println(mb2.map(i), DEC);
  }
  Serial.println();

  Serial.println("Done...");
}


void loop()
{

}


// -- END OF FILE --
