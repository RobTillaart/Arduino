//
//    FILE: sparse_matrix_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurement functions
//     URL: https://github.com/RobTillaart/SparseMatrix

#include  "SparseMatrix.h"


SparseMatrix sm(20);

uint32_t start, stop;
uint32_t duration;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println();
  Serial.println(SPARSEMATRIX_LIB_VERSION);
  Serial.println(sm.size());
  Serial.println(sm.count());
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sm.set(i, i, 5);
  }
  stop = micros();
  Serial.print("set 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sm.set(i, i, 4);
  }
  stop = micros();
  Serial.print("redo 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 20; i < 40; i++)
  {
    sm.set(i, i, 5);
  }
  stop = micros();
  Serial.print("full 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sm.add(i, i, 5);
  }
  stop = micros();
  Serial.print("add 20x :\t");
  Serial.println(stop - start);
  delay(100);

  volatile float f;
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    f = sm.get(i, i);
  }
  stop = micros();
  Serial.print("get 20x :\t");
  Serial.println(stop - start);
  Serial.println(f);
  delay(100);

  start = micros();
  f = sm.sum();
  stop = micros();
  Serial.print("sum 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sm.clear();
  }
  stop = micros();
  Serial.print("clr 20x :\t");
  Serial.println(stop - start);
  delay(100);
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
