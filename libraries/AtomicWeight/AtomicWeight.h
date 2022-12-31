#pragma once
//
//    FILE: AtomicWeight.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.1.2
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"

#define ATOMIC_WEIGHT_LIB_VERSION         (F("0.1.2"))


/////////////////////////////////////////////////////////////////////////
//
//  PERIODIC TABLE OF ELEMENTS Class
//
class PTOE
{
public:
  PTOE(uint8_t size = 118);    //  all by default
  uint8_t size();


  uint8_t electrons(uint8_t el);
  uint8_t neutrons(uint8_t el);
  uint8_t protons(uint8_t el);


  float   weight(uint8_t el);
  float   weight(const char * formula);
  float   weight(char * formula);


  char *  name(uint8_t el);
  uint8_t find(const char * abbrev);
  uint8_t find(char * abbrev);


  //  DEBUG
  float   weightFactor();


private:
  uint8_t     _size;
  const float _weightFactor = 1.0 / 222.909;
  
  float       _weight(char sep);
  char        *p;  //  for _weight().
};



// -- END OF FILE --

