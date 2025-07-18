//
//    FILE: multimap_2d.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo mapping an angle on a semi-circle (2D {x, y} position)
//     URL: https://github.com/RobTillaart/MultiMap
//
//  when printing into a plotter one sees a rough sine and cosine
//  with an amplitude of 5, approximated with interpolation.

#include "MultiMap.h"

float in[]  = { 0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360 };
float xc[] = { 5, 4, 3, 0, -3, -4, -5, -4, -3,  0,  3,  4, 5 };
float yc[] = { 0, 3, 4, 5,  4,  3,  0, -3, -4, -5, -4, -3, 0 };


int size = 13;


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();

  Serial.println("I\tX\tY");

  for (int i = 0; i <= 360; i++)
  {
    //  2D mapping is doen by mapping twice (not too efficient but it works sort of.
    float x = multiMap<float>(i, in, xc, size);
    float y = multiMap<float>(i, in, yc, size);
    // Serial.print(i);
    // Serial.print("\t");
    Serial.print(x, 1);  //  1 decimal
    Serial.print("\t");
    Serial.println(y, 1);  //  1 decimal
  }
}


void loop()
{
}


//  -- END OF FILE --
