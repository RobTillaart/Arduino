//
//    FILE: SIMON_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SIMON


#include "simon.h"

SIMON simon;

uint32_t  count = 0;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("SIMON_LIB_VERSION:\t");
  Serial.println(SIMON_LIB_VERSION);

  Serial.println("10x GENERATE");
  delay(100);
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    simon.generateSequence(4, 0, 9);;
  }
  stop = micros();
  Serial.print("time:\t");
  Serial.println(stop - start);


  Serial.println("10x ADD + CLEAR");
  delay(100);
  start = micros();
  simon.clear();
  for (int i = 0; i < 10; i++)
  {
    simon.add(i);
  }
  stop = micros();
  Serial.print("time:\t");
  Serial.println(stop - start);


  Serial.println("10x VERIFY");
  delay(100);
  start = micros();
  for (int i = 0; i < 10; i++)
  {
    simon.verify();
  }
  stop = micros();
  Serial.print("time:\t");
  Serial.println(stop - start);

}


void loop()
{
}

// -- END OF FILE --
