//
//    FILE: multimap_timing.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-09
//    (c) : MIT
//
// example measures the performance of multiMap <int> vs <float>


#include "MultiMap.h"

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
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  float x = multiMap<int>(12, in, out, 3);
  stop = micros();
  Serial.print("time <int>: \t");
  Serial.println(stop - start);
  Serial.println(x, 4);
  delay(10);  //  make sure print has ended

  start = micros();
  float y = multiMap<float>(12, fin, fout, 3);
  stop = micros();
  Serial.print("time <float>: \t");
  Serial.println(stop - start);
  Serial.println(y, 4);
  delay(10);  //  make sure print has ended

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

