//
//    FILE: sparse_matrix_max.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo max size matrix.
//     URL: https://github.com/RobTillaart/SparseMatrix


#include  "SparseMatrix.h"


SparseMatrix sm(255);  // max 255 elements.

uint32_t start, stop;
uint32_t duration;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println(sm.size());
  Serial.println(sm.count());
  Serial.println();
  delay(100);

  //  one element per row
  for (int i = 0; i < 255; i++)
  {
    sm.set(i, random(256), random(100000));
  }

  //  this dump takes a while !
  dump(255, 255);
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
