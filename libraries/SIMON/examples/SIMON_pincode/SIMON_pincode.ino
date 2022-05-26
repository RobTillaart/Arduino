//
//    FILE: SIMON_pincode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo: how many tries for breaking a 4 digit code randomly
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

  simon.generateSequence(4, 0, 9);
}


void loop()
{
  // try to guess pin code
  count++;
  simon.clear();
  for (int i = 0; i < 4; i++)
  {
    simon.add(random(10));
  }
  if (simon.verify())
  {
    Serial.print(millis());
    Serial.print("\t tries:\t ");
    Serial.println(count);
    count = 0;
    simon.generateSequence(4, 0, 9);
  }
}

// -- END OF FILE --
