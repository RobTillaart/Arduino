#pragma once
//
//    FILE: gamma.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.1
//    DATE: 2020-08-08
// PURPOSE: Arduino Library to efficiently hold a gamma lookup table


#include "Arduino.h"

#define GAMMA_LIB_VERSION                 (F("0.4.1"))

#define GAMMA_DEFAULT_SIZE                32
#define GAMMA_MAX_SIZE                    256


class GAMMA
{

public:

  GAMMA(uint16_t size = GAMMA_DEFAULT_SIZE);
  ~GAMMA();

  //  allocates memory
  //  sets default gamma = 2.8
  //  Returns false if allocation fails
  bool begin();

  //  CORE
  //  Returns false if gamma <= 0
  bool  setGamma(float gamma);
  float getGamma();
  //  access values with index operator
  //  index = 0 .. size
  uint8_t operator[] (uint8_t index);

  //  META INFO
  uint16_t size();
  uint16_t distinct();

  //  DEBUG
  bool dump(Stream *str = &Serial);
  bool dumpArray(Stream *str = &Serial);


private:
  uint8_t   _shift    = 0;
  uint8_t   _mask     = 0;
  uint16_t  _size     = 0;
  uint8_t   _interval = 0;
  float     _gamma    = 1.0;  //  1.0 == no gamma, linear.
  uint8_t * _table    = NULL;

  float     fastPow(float a, float b);
};


//  -- END OF FILE --

