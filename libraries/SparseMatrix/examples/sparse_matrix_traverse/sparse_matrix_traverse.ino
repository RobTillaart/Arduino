//
//    FILE: sparse_matrix_traverse.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SparseMatrix


#include  "SparseMatrix.h"


SparseMatrix sm(30);

uint8_t x;
uint8_t y;
float value;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SPARSEMATRIX_LIB_VERSION: ");
  Serial.println(SPARSEMATRIX_LIB_VERSION);
  Serial.println();

  Serial.println(sm.size());
  Serial.println(sm.count());
  Serial.println();

  //  10 x 10 matrix
  for (int i = 0; i < 30; i++)
  {
    x = random(10);
    y = random(10);
    value = EULER * PI * random(37);
    bool b = sm.set(x, y, value);  //  check full
    if (b) Serial.print('.');
  }
  Serial.println();
  Serial.println();
  dump(10, 10);

  Serial.println("POS\tX\tY\tVALUE");
  bool exists = sm.first(x, y, value);
  int pos = 0;
  while (exists)
  {
    Serial.print(pos++);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(value);
    Serial.println();
    exists = sm.next(x, y, value);
  }
  Serial.println();

  Serial.println("POS\tX\tY\tVALUE");
  exists = sm.last(x, y, value);
  pos = sm.count() - 1;
  while (exists)
  {
    Serial.print(pos--);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(value);
    Serial.println();
    exists = sm.prev(x, y, value);
  }
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
