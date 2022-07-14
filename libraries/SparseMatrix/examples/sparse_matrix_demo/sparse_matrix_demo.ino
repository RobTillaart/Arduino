//
//    FILE: sparse_matrix_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SparseMatrix


#include  "SparseMatrix.h"


SparseMatrix sm(20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println(sm.size());
  Serial.println(sm.count());
  Serial.println();

  //  30 x 10 matrix
  for (int i = 0; i < 30; i++)
  {
    uint8_t x = random(10);
    uint8_t y = random(10);
    float value = EULER * PI * random(37);
    bool b = sm.set(x, y, value);  // check full
    if (b) Serial.print('.');
  }
  Serial.println();
  dump(10, 10);

  for (int y = 0; y < 10; y++)
  {
    sm.set(3, y, 0);
  }
  dump(10, 10);

  for (int y = 0; y < 10; y++)
  {
    bool b = sm.add(0, y, -1);
    if (b == false) Serial.print('e');
  }
  Serial.println();
  dump(10, 10);

  sm.clear();
  Serial.println();
  dump(10, 10);

  for (int y = 0; y < 10; y++)
  {
    sm.add(y, y, 5);
  }
  Serial.println();
  dump(10, 10);

  for (int y = 0; y < 10; y++)
  {
    sm.add(y, y, -5);
  }
  Serial.println();
  dump(10, 10);
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
