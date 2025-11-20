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
  Serial.print("SPARSEMATRIX_LIB_VERSION: ");
  Serial.println(SPARSEMATRIX_LIB_VERSION);
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

  Serial.print("\tBounding Box");
  Serial.print("\t");
  Serial.print(minX);
  Serial.print("\t");
  Serial.print(maxX);
  Serial.print("\t");
  Serial.print(minY);
  Serial.print("\t");
  Serial.print(maxY);
  Serial.println();

  sm.boundingBoxX(minX, maxX);

  Serial.print("\tBounding Box X");
  Serial.print("\t");
  Serial.print(minX);
  Serial.print("\t");
  Serial.print(maxX);
  Serial.println();

  sm.boundingBoxY(minY, maxY);

  Serial.print("\tBounding Box Y");
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
  Serial.print("SIZE: \t");
  Serial.println(sm.size());
  Serial.print("COUNT:\t");
  Serial.println(sm.count());
  Serial.print("MATRIX:\t");
  Serial.print(sx);
  Serial.print("x");
  Serial.println(sy);
  Serial.print("SUM:\t");
  Serial.println(sm.sum());
  Serial.println();

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
