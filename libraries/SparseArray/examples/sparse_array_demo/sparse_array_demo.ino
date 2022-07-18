//
//    FILE: sparse_array_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SparseArray


#include  "SparseArray.h"

//  assume a sparse array of 100 floats
//  filled with max of 20 non-zero elements == 20%
SparseArray sar(20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println(sar.size());
  Serial.println(sar.count());
  Serial.println();

  for (int i = 0; i < 20; i++)
  {
    uint8_t x = random(100);   //  100 elements of max 255..
    float value = EULER * PI * random(37);
    bool b = sar.set(x, value);  // check full
    if (b) Serial.print('.');
  }
  Serial.println();
  dump(100);

  Serial.println();
  Serial.print("NORMAL ARRAY: ");
  Serial.println(100 * 4);          //  sizeof float
  Serial.print("SPARSE ARRAY: ");
  Serial.println(sar.size() * 6);
}


void loop()
{
}


void dump(uint8_t sx)
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

  for (int x = 0; x < sx; x++)
  {
    if (x % 10 == 0) Serial.println();
    Serial.print(sar.get(x));
    Serial.print('\t');
  }
  Serial.println();
}


//  -- END OF FILE --
