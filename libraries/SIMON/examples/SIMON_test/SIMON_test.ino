//
//    FILE: SIMON_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic functionality
//    DATE: 2022-05-26
//     URL: https://github.com/RobTillaart/SIMON

#include "simon.h"

SIMON simon;

uint8_t seq[7] = { 0, 1, 2, 3, 4, 5, 6 };


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("SIMON_LIB_VERSION:\t");
  Serial.println(SIMON_LIB_VERSION);

  test_1();
}


void loop()
{
}


void test_1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  
  for (int i = 0; i < 8; i++)
  {
    Serial.print(simon.setSequence(seq, i));
    Serial.print('\t');
    Serial.println(simon.size());
  }
  Serial.println();

  //  expected 2x false
  Serial.println(simon.setSequence(seq, 12));  // expect 0
  Serial.println(simon.setSequence(NULL, 5));  // expect 0
  Serial.println();

  simon.setSequence(seq, 7);
  for (int i = 0; i < 7; i++)
  {
    simon.add(i);
  }
  Serial.println(simon.verify());  // expect 1

  simon.clear();
  for (int i = 0; i < 7; i++)
  {
    simon.add(42);
  }
  Serial.println(simon.verify());  // expect 0
  Serial.println();
}


// -- END OF FILE --
