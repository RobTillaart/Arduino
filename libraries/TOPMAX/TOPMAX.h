#pragma once
//
//    FILE: TOPMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-05-18
// PURPOSE: Arduino library to track top n maxima.
//     URL: https://github.com/RobTillaart/TOPMAX


#define TOPMAX_LIB_VERSION             (F("0.1.0"))


#include "Arduino.h"


class TOPMAX
{
public:
  TOPMAX(uint8_t size = 5);
  ~TOPMAX();

  uint8_t count();
  uint8_t size();
  void    reset();
  bool    add(float value);
  float   get(uint8_t index);
  void    fill(float value);


private:
  uint8_t _size;
  uint8_t _count;
  float * _arr;
};


//  -- END OF FILE --

