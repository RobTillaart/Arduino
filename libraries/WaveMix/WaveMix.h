#pragma once
//
//    FILE: WaveMix.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: an Arduino library to mix two signals (A and B) with an adaptive weight.
//     URL: https://github.com/RobTillaart/CountDown
//


#include "Arduino.h"

#define WAVEMIX_LIB_VERSION               (F("0.1.0"))


class WaveMix
{
public:
  explicit WaveMix();

  //  w1 >= 0 && w2 >= 0 && (w1+w2) > 0
  void  setWeight(float w1, float w2);
  float getW1() { return _w1; };
  float getW2() { return _w2; };
  //  0 <= p <= 100
  void  setPercentage(float p);


  float mix(float s1, float s2);

private:
  float _w1 = 0.5;
  float _w2 = 0.5;
};


// -- END OF FILE --
