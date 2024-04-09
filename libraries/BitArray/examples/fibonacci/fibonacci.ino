//    FILE: Fibonacci.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Generate Fibonacci numbers with bit array
//     URL: https://github.com/RobTillaart/BitArray
//     URL: https://forum.arduino.cc/index.php?topic=532760.0


#include "BitArray.h"


#define NR 70

BitArray a;
BitArray b;


void setup()
{
  Serial.begin(230400);

  //  10 bit can hold 3 digits 000..999 (1000 with overflow)
  //  10 bits give effective use of 1000/1024 = 97%
  int x = a.begin(10, NR);
  if (x != 0) Serial.println(x);
  x = b.begin(10, NR);
  if (x != 0) Serial.println(x);

  a.clear();
  b.clear();

  b.set(0, 1);

  uint32_t start = millis();
  for (int x = 0; x <= 1000; x++)
  {
    {
      Serial.print(x);
      Serial.write('\t');
      for (int16_t i = NR - 1; i >= 0; i--)
      {
        uint32_t t = a.get(i);
        if (t < 100) Serial.write('0');
        if (t < 10) Serial.write('0');
        Serial.print(t);
      }
      Serial.write('\n');
    }
    add();
  }
  Serial.println(millis() - start);
}


void loop()
{}


//  add numbers in groups of 3 digits
void add()
{
  uint8_t carry = 0;

  for (uint16_t i = 0; i <= NR; i++)
  {
    uint16_t ta = a.get(i);
    uint16_t tb = b.get(i);

    //  if there is nothing to add, skip column
    if (ta == 0 && tb == 0 && carry == 0) continue;

    //  do the add
    uint16_t tc = ta + tb + carry;
    //  does column overflow? then correct
    if (tc > 999)
    {
      tc -= 1000;
      carry = 1;  //  carry for next column
    }
    else carry = 0;
    b.set(i, tc);
    a.set(i, tb);
  }
}


//  -- END OF FILE --

