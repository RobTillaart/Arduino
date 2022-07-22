//
//    FILE: distanceTable_pascal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of memory efficient distance table class
//    DATE: 2015-06-18
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "DistanceTable.h"


//  above 27 layout fails
//  above 29 allocation fails
#define MAXSIZE     27

DistanceTable dt(MAXSIZE);


void setup()
{
  Serial.begin(115200);
  Serial.print("\nDistanceTable: ");
  Serial.println(DISTANCETABLE_LIB_VERSION);
  Serial.println("Pascals triangle");

  dt.clear();

  //  FILL THE 1's
  for (int y = 1; y < MAXSIZE; y++)
  {
    dt.set(0, y, 1);
  }
  for (int x = 1; x < MAXSIZE; x++)
  {
    dt.set(x, x + 1, 1);
  }

  //  ADD EMPTY ELEMENTS PER ROW
  for (int y = 0; y < MAXSIZE; y++)
  {
    for (int x = 0; x < y; x++)
    {
      if (dt.get(x, y) == 0)
      {
        float p = dt.get(x - 1, y - 1) + dt.get(x, y - 1);
        dt.set(x, y, p);
      }
    }
  }

  //  PRINT LOWER HALF TRIANGLE
  Serial.println();
  for (uint8_t i = 0; i < MAXSIZE; i++)
  {
    for (uint8_t j = 0; j < i; j++)
    {
      Serial.print(dt.get(i, j), 0);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --
