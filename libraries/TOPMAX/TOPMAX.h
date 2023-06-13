#pragma once
//
//    FILE: TOPMAX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2023-05-18
// PURPOSE: Arduino library to track top n maxima.
//     URL: https://github.com/RobTillaart/TOPMAX


#define TOPMAX_LIB_VERSION             (F("0.1.1"))


#include "Arduino.h"


class TOPMAX
{
public:
  TOPMAX(uint8_t size = 5);
  ~TOPMAX();

  uint8_t count();
  uint8_t size();
  void    reset();
  virtual bool add(float value);
  virtual void fill(float value);
  float   getValue(uint8_t index);


protected:
  uint8_t _size;
  uint8_t _count;
  float * _arr;
};


////////////////////////////////////////////////////
//
//  DERIVED
//
class TOPMAXext : public TOPMAX
{
public:
  TOPMAXext(uint8_t size = 5);
  ~TOPMAXext();
  
  bool     add(float value, uint32_t tag);
  uint32_t getTag(uint8_t index);
  void     fill(float value, uint32_t tag);

private:
  uint32_t * _tag;
};


//  -- END OF FILE --

