#pragma once
//
//    FILE: gamma.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2020-08-08
// PURPOSE: Arduino Library to efficiently hold a gamma lookup table


#include "Arduino.h"

#define GAMMA_LIB_VERSION         (F("0.2.2"))

#define GAMMA_DEFAULT_SIZE        32
#define GAMMA_MAX_SIZE            256


class GAMMA
{

public:

  GAMMA(uint16_t size = GAMMA_DEFAULT_SIZE);
  ~GAMMA();

  //  allocates memory
  //  sets default gamma = 2.8
  void begin();

  //  CORE
  void setGamma(float gamma);
  float getGamma();
  //  access values with index operator
  uint8_t operator[] (uint8_t index);

  //  META INFO
  uint16_t size();
  uint16_t distinct();

  //  DEBUG
  void dump(Stream *str = &Serial);
  void dumpArray(Stream *str = &Serial);


private:
  uint8_t   _shift    = 0;
  uint8_t   _mask     = 0;
  uint16_t  _size     = 0;
  uint8_t   _interval = 0;
  float     _gamma    = 0;
  uint8_t * _table    = NULL;
};


// -- END OF FILE --

