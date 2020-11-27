//
//    FILE: multimap_timing.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-04-09
//    (c) : MIT
//


#include "multimap.h"

int in[] =  { 11,  22,  33};
int out[] = {111, 222, 555};

float fin[]  = { 11, 22, 33};
float fout[] = {111, 222, 555};

uint32_t start;
uint32_t stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  delay(10);  // make sure print has ended

  start = micros();
  float x = multiMap<int>(12, in, out, 3);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x, 4);
  delay(10);  // make sure print has ended

  start = micros();
  float y = multiMap<float>(12, fin, fout, 3);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(y, 4);
}

void loop()
{

}

// -- END OF FILE --
