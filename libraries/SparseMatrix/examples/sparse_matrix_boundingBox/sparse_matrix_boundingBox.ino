//
//    FILE: sparse_matrix_boundingBox.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SparseMatrix


#include  "SparseMatrix.h"


SparseMatrix sm(10);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  //  10 x 10 matrix - 6 random elements in the middle
  for (int i = 0; i < 6; i++)
  {
    uint8_t x = random(5) + 3;
    uint8_t y = random(5) + 3;
    sm.set(x, y, random(37));
  }
  dump(10, 10);

  uint8_t minX, maxX, minY, maxY;
  sm.boundingBox(minX, maxX, minY, maxY);

  Serial.println("\tBounding Box");
  Serial.print("\t");
  Serial.print(minX);
  Serial.print("\t");
  Serial.print(maxX);
  Serial.print("\t");
  Serial.print(minY);
  Serial.print("\t");
  Serial.print(maxY);
  Serial.println();
}


void loop()
{
}


void dump(uint8_t sx, uint8_t sy)
{
  Serial.println();
  Serial.print("DUMP\t");

  Serial.print(sm.size());
  Serial.print("\t");
  Serial.print(sm.count());
  Serial.print("\t");

  Serial.print(sx);
  Serial.print("x");
  Serial.print(sy);
  Serial.print("\t");
  Serial.println(sm.sum());
  for (int y = 0; y < sy; y++)
  {
    for (int x = 0; x < sx; x++)
    {
      Serial.print(sm.get(x, y));
      Serial.print('\t');
    }
    Serial.println();
  }
  Serial.println();
}


//  -- END OF FILE --
