//
//    FILE: sparse_array_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurement functions
//     URL: https://github.com/RobTillaart/SparseArray

#include  "SparseArray.h"


SparseArray sar(20);

uint32_t start, stop;
uint32_t duration;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println();
  Serial.println(SPARSEARRAY_LIB_VERSION);
  Serial.println(sar.size());
  Serial.println(sar.count());
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sar.set(i, 5);
  }
  stop = micros();
  Serial.print("set 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sar.set(i, 4);
  }
  stop = micros();
  Serial.print("redo 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 20; i < 40; i++)
  {
    sar.set(i, 5);
  }
  stop = micros();
  Serial.print("full 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sar.add(i, 5);
  }
  stop = micros();
  Serial.print("add 20x :\t");
  Serial.println(stop - start);
  delay(100);

  volatile float f;
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    f = sar.get(i);
  }
  stop = micros();
  Serial.print("get 20x :\t");
  Serial.println(stop - start);
  Serial.println(f);
  delay(100);

  start = micros();
  f = sar.sum();
  stop = micros();
  Serial.print("sum 20x :\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  for (int i = 0; i < 20; i++)
  {
    sar.clear();
  }
  stop = micros();
  Serial.print("clr 20x :\t");
  Serial.println(stop - start);
  delay(100);
}


void loop()
{
}


void dump(uint16_t sx)
{
  Serial.println();
  Serial.print("DUMP\t");

  Serial.print(sar.size());
  Serial.print("\t");
  Serial.print(sar.count());
  Serial.print("\t");

  Serial.print(sx);
  Serial.print("\t");
  Serial.println(sar.sum());
  for (uint16_t x = 0; x < sx; x++)
  {
    if (x % 10 == 0) Serial.println();
    Serial.print(sar.get(x));
    Serial.print('\t');
  }
  Serial.println();
}


//  -- END OF FILE --
