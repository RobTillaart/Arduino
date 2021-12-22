//
//    FILE: nibbleArray_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo nibble array
//    DATE: 2020-06-21
//     URL: https://github.com/RobTillaart/nibbleArray


#include "nibbleArray.h"

nibbleArray na(500);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("NIBBLEARRAY_LIB_VERSION: ");
  Serial.println(NIBBLEARRAY_LIB_VERSION);

  test_1();

  Serial.println("\nDone...");
}


void test_1()
{
  int ar[16];
  for (int i = 0; i < 16; i++) ar[i] = 0;

  na.clear();

  // 500 throws with 3 dices (3..18 ==> 0..15)
  for (int i = 0; i < 500; i++)
  {
    uint8_t sum = random(6);  // 0..5
    sum += random(6);
    sum += random(6);
    na.set(i, sum);       // diff from na.set(i, random(16));
  }

  for (int i = 0; i < 500; i++)
  {
    ar[na.get(i)]++;
    Serial.print(" ");
    Serial.print(na.get(i), HEX);
    if ((i % 32) == 31) Serial.println();
  }
  Serial.println();

  Serial.println("\nFrequency analysis");
  for (int i = 0; i < 16; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    // for (int p = 0; p < ar[i]; p++) Serial.print(">");
    Serial.print(ar[i]);
    Serial.println();
  }
  Serial.println();

  Serial.println("\ninterpret data as a route");
  for (int i = 0; i < 20; )
  {
    uint8_t s = na.get(i++);
    uint8_t d = na.get(i++);
    move(s, d);
  }

  Serial.println("\nor store music in the array");
  for (int i = 0; i < 30; )
  {
    uint8_t octave   = na.get(i++);
    uint8_t note     = na.get(i++);
    uint8_t duration = na.get(i++); // in 1/16th
    play(octave, note, duration);
    // sendMIDI(note, duration);
  }
}


void play(uint8_t octave, uint8_t note, uint8_t duration)
{
  Serial.print("Play: ");
  // Serial.print(octave);
  Serial.print(" ");
  switch (note)
  {
    case 0:  Serial.print("C  "); break;
    case 1:  Serial.print("C# "); break;
    case 2:  Serial.print("D  "); break;
    case 3:  Serial.print("D# "); break;
    case 4:  Serial.print("E  "); break;
    case 5:  Serial.print("F  "); break;
    case 6:  Serial.print("F# "); break;
    case 7:  Serial.print("G  "); break;
    case 8:  Serial.print("G# "); break;
    case 9:  Serial.print("A  "); break;
    case 10: Serial.print("A# "); break;
    case 11: Serial.print("B  "); break;
    case 12: Serial.print("C  "); break;
    case 13: Serial.print("C# "); break;
    case 14: Serial.print("D  "); break;
    case 15: Serial.print(" - "); break;
  }
  for (uint8_t i = 0; i < duration; i++)
  {
    delay(1000 / 16);
    Serial.print(".");
  }
  Serial.println();
}


void move(uint8_t steps, uint8_t direction)
{
  Serial.print(steps);
  Serial.print(" steps to the ");
  switch (direction)
  {
    case 0:  Serial.print("N");   break;
    case 1:  Serial.print("NNO"); break;
    case 2:  Serial.print("NO");  break;
    case 3:  Serial.print("ONO"); break;
    case 4:  Serial.print("O");   break;
    case 5:  Serial.print("OZO"); break;
    case 6:  Serial.print("ZO");  break;
    case 7:  Serial.print("ZZO"); break;
    case 8:  Serial.print("Z");   break;
    case 9:  Serial.print("ZZW"); break;
    case 10: Serial.print("ZW");  break;
    case 11: Serial.print("WZW"); break;
    case 12: Serial.print("W");   break;
    case 13: Serial.print("WNW"); break;
    case 14: Serial.print("NW");  break;
    case 15: Serial.print("NNW"); break;
  }
  Serial.println();
  delay(100 * steps);
}


void loop()
{
}


// -- END OF FILE --

