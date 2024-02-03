//
//    FILE: map2bits_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2bits demo
//     URL: https://github.com/RobTillaart/map2bits


#include "map2bits.h"

map2bits mb;

volatile uint32_t x = 0;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAP2BITS_LIB_VERSION: ");
  Serial.println(MAP2BITS_LIB_VERSION);
  Serial.println();
  delay(100);


  mb.init(0, 1000, 10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = mb.map(i);
  }
  stop = micros();
  Serial.println("1000 x map (full)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 1000.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);


  mb.init(100, 200, 10);
  start = micros();
  for (int i = 0; i < 300; i++)
  {
    x = mb.map(i);
  }
  stop = micros();
  Serial.println("3 x 100 x map (constrained)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 300.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);

  Serial.println();
  Serial.println("Done...");
}


void loop()
{

}


// -- END OF FILE --
