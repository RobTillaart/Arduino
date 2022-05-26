//
//    FILE: SIMON_letters.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo:
//    DATE: 2022-05-26
//     URL: https://github.com/RobTillaart/SIMON

#include "simon.h"

SIMON simon;

uint32_t  count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("SIMON_LIB_VERSION:\t");
  Serial.println(SIMON_LIB_VERSION);

  //  casting to (uint8_t *)  prevents warnings.
  simon.setSequence((uint8_t *)"Hello", 5);

  simon.clear();
  simon.add('H');
  simon.add('e');
  simon.add('l');
  simon.add('l');
  simon.add('o');
  Serial.println(simon.verify());  // expect 1

  simon.clear();
  simon.add('h');
  simon.add('e');
  simon.add('l');
  simon.add('l');
  simon.add('o');
  Serial.println(simon.verify());  // expect 0

  //  casting to (uint8_t *)  prevents warnings.
  Serial.println(simon.verify((uint8_t *)"Hello", 5));  // expect 1
  Serial.println(simon.verify((uint8_t *)"hello", 5));  // expect 0

}


void loop()
{
}

// -- END OF FILE --
