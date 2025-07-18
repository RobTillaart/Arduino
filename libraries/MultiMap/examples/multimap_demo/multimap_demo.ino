//
//    FILE: multimap_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/MultiMap
//     URL: https://forum.arduino.cc/t/messy-math-with-map-and-pow/1275821
//          https://wokwi.com/projects/401812192306752513


#include "MultiMap.h"

//  not the IN array is not equidistant.
//  layout is to see the points of the graph.
float in[]  = { 0, 20,  40,  50,  60,   80,   90,   100, 105 };
float out[] = { 1, 2.8, 4.5, 7.0, 10.4, 33.5, 57.5, 100, 120 };

int size = 9;


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();

  Serial.println("X\tY");

  for (int i = 0; i <= 500; i++)
  {
    float x = i * 0.2;
    float y = multiMap<float>(x, in, out, size);
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y, 1);  //  1 decimal
  }
}


void loop()
{
}


//  -- END OF FILE --
