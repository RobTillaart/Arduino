//
//    FILE: sparse_array_max.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo max size array
//     URL: https://github.com/RobTillaart/SparseArray


#include  "SparseArray.h"

//  assume a sparse array of 2000 floats
//  filled with max of 200 non-zero elements == 10%
SparseArray sar(200);

uint32_t start, stop;
uint32_t duration;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println(sar.size());
  Serial.println(sar.count());
  Serial.println();
  delay(100);


  for (int i = 0; i < 200; i++)
  {
    sar.set(random(2000), random(1000));
  }

  //  this dump takes a while !
  dump(2000);
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
