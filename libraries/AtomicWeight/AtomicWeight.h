#pragma once
//
//    FILE: AtomicWeight.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.1.3
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"

#define ATOMIC_WEIGHT_LIB_VERSION         (F("0.1.3"))


/////////////////////////////////////////////////////////////////////////
//
//  PERIODIC TABLE OF ELEMENTS Class
//
class PTOE
{
public:
  PTOE(const uint8_t size = 118);    //  all by default
  uint8_t size();


  uint8_t electrons(const uint8_t el);
  uint8_t neutrons(const uint8_t el);
  uint8_t protons(const uint8_t el);

  //  weight of one atom 
  float   weight(const uint8_t el);

  //  if (el != NULL) weights one element in a formula, e.g el == "H"
  //  if (el == NULL) weights the whole formula
  float   weight(const char * formula, const char * el = NULL);
 
  //  mass percentage of one element in a formula.
  float   massPercentage(const char * formula, const char * el);

  char *  name(const uint8_t el);
  uint8_t find(const char * abbrev);


  //  DEBUG
  float   weightFactor();


private:
  uint8_t     _size;
  const float _weightFactor = 1.0 / 222.909;
  
  //  if (el == NULL) ==> whole weight otherwise only of element.
  float       _weight(char sep, const char * el);
  char        *p;  //  for _weight().
};


// -- END OF FILE --

