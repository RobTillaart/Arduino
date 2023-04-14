#pragma once
//
//    FILE: AtomicWeight.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.1.5
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"

#define ATOMIC_WEIGHT_LIB_VERSION         (F("0.1.5"))


#ifndef ATOMIC_WEIGHT_MAX_SPLIT_LIST
#define ATOMIC_WEIGHT_MAX_SPLIT_LIST 20
#endif


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
  float   weight(const char * formula, const char * abbrev = NULL);
  //  mass percentage of one element in a formula.
  float   massPercentage(const char * formula, const char * abbrev);


  char *  name(const uint8_t el);
  uint8_t find(const char * abbrev);


  //  CONVERSION
  float   moles2grams(const char * formula, float moles = 1.0);
  float   grams2moles(const char * formula, float grams = 1.0);


  //  DEBUG
  float   weightFactor();


  ////////////////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL 0.1.4
  //
  //  SPLIT FORMULA IN ELEMENTS
  uint8_t splitElements(const char * formula);
  uint8_t element(uint8_t el);


  //  if (el != NULL) count atoms of one element in a formula, e.g el == "H"
  //  if (el == NULL) count all atoms in the whole formula
  uint32_t count(const char * formula, const char * el = NULL);
  //  atom percentage of one element in a formula.
  float   atomPercentage(const char * formula, const char * el);


private:
  uint8_t     _size;
  const float _weightFactor = 1.0 / 222.909;

  //  if (el == NULL) ==> whole weight otherwise only of element.
  float       _weight(char sep, const char * abbrev);
  uint32_t    _count(const char sep, const char * abbrev);
  char        *p;  //  for _weight() and _count()

  //  for splitElements
  uint8_t     _splitList[ATOMIC_WEIGHT_MAX_SPLIT_LIST]; //  default 20
  uint8_t     _found;
};


//  -- END OF FILE --

