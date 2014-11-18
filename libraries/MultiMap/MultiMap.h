//
//    FILE: multiMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: MultiMap library for Arduino
//     URL: http://playground.arduino.cc/Main/MultiMap
//
// HISTORY: see playground article
//

#ifndef multimap_h
#define multimap_h

#define MULTIMAP_LIB_VERSION "0.1.00"

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// note: the in array should have increasing values
template<typename T>
T multiMap(T val, T* _in, T* _out, uint8_t size)
{
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0]) return _out[0];
    if (val >= _in[size-1]) return _out[size-1];

    // search right interval
    uint8_t pos = 1;  // _in[0] allready tested
    while(val > _in[pos]) pos++;

    // this will handle all exact "points" in the _in array
    if (val == _in[pos]) return _out[pos];

    // interpolate in the right segment for the rest
    return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

/*
#include "multiMap.h"

int in[] = {11,22,33};
int out[] = {111,222,555};

float fin[] = {11,22,33};
float fout[] = {111,222,555};

uint32_t start;
uint32_t stop;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start ");

  start = micros();
  float  x = multiMap<int>(12, in, out, 3);  
  stop = micros();
  Serial.println(stop-start);  
  Serial.println(x);

  start = micros();
  float  y = multiMap<float>(12, fin, fout, 3);
  stop = micros();
  Serial.println(stop-start);
  Serial.println(y);
}

void loop() {}
*/
#endif
//
// END OF FILE
//