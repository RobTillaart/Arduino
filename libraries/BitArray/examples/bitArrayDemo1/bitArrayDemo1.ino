//
//    FILE: bitArrayDemo1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/BitArray


#include "BitArray.h"


BitArray b;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("LIB VERSION:\t");
  Serial.println(BITARRAY_LIB_VERSION);

  //  shows reclaiming memory
  test(10, 1000);  //  1024 steps
  test(6, 1000);   //  64 steps
  test(4, 3000);   //  16 steps
}


void test(byte bits, uint16_t samples)
{
  b.begin(bits, samples);

  Serial.print("CAPACITY:\t");
  Serial.println(b.capacity());
  Serial.print("  MEMORY:\t");
  Serial.println(b.memory());
  Serial.print("    BITS:\t");
  Serial.println(b.bits());
  Serial.print("SEGMENTS:\t");
  Serial.println(b.segments());

  for (int i = 0; i < samples; i++)
  {
    uint16_t x = analogRead(A0) >> (10 - bits);  //  note resized sample!
    b.set(i, x);
  }
  Serial.println("\nSAMPLES:\t");
  for (int i = 0; i < samples; i++)
  {
    if (i % 10 == 0)
    {
      Serial.println();
      Serial.print(i, DEC);
      Serial.print(")\t");
    }
    Serial.print(b.get(i));
    Serial.print("\t");
  }
  Serial.println("\n\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

