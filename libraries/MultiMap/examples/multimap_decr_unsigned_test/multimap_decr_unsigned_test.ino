//
//    FILE: multimap_decr_unsigned_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/MultiMap
//
//  test for issue #15, decreasing unsigned

#include "MultiMap.h"

//  note the IN array is not equidistant.
//  layout is to see the points of the graph.
float in[] = { 0, 20, 40, 50, 60, 80, 90, 100, 105 };
uint16_t out[] = { 1000, 900, 800, 600, 300, 150, 75, 40, 20 };

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
    float y = multiMap<float, uint16_t>(x, in, out, size);
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y, 1);  //  1 decimal
  }
}


void loop()
{
}


//  -- END OF FILE --
