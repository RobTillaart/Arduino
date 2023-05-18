#pragma once
//
//    FILE: TOPMIN.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-05-18
// PURPOSE: Arduino library to track top n minima.
//     URL: https://github.com/RobTillaart/TOPMIN


#define TOPMIN_LIB_VERSION             (F("0.1.0"))


#include "Arduino.h"


class TOPMIN
{
public:
  TOPMIN(uint8_t size = 5);
  ~TOPMIN();

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

