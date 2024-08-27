#pragma once
//
//    FILE: AtomicWeight.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.3.0
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"


#define ATOMIC_WEIGHT_LIB_VERSION         (F("0.3.0"))


#ifndef ATOMIC_WEIGHT_MAX_SPLIT_LIST
#define ATOMIC_WEIGHT_MAX_SPLIT_LIST 20
#endif


//  Miscellaneous related constants.
const float AVOGADRO            = 6.02214076e+23;       //  1.0 / DALTON.
const float DALTON              = 1.66053907e-24;       //  weight in grams of one nucleon.
const float PROTON_WEIGHT       = 1.6726231e-24;        //
const float NEUTRON_WEIGHT      = 1.6749286e-24;        //
const float ELECTRON_WEIGHT     = 9.10938356e-28;       //  weight in grams of one electron.
const float DALTON2EV           = 931494697.25613;      //


/////////////////////////////////////////////////////////////////////////
//
//  PERIODIC TABLE OF ELEMENTS Class
//
class PTOE
{
public:
  PTOE(const uint8_t size = 118);    //  all by default
  uint8_t size();


  //  BASIC
  char *   name(const uint8_t element);
  uint8_t  find(const char * abbrev);

  uint8_t  electrons(const uint8_t element);
  uint8_t  neutrons(const uint8_t element);
  uint8_t  protons(const uint8_t element);


  //  WEIGHT of one atom
  float    weight(const uint8_t element);
  //  if (element != NULL) weights one element in a formula, e.g element == "H"
  //  if (element == NULL) weights the whole formula
  float    weight(const char * formula, const char * abbrev = NULL);
  //  mass percentage of one element in a formula.
  float    massPercentage(const char * formula, const char * abbrev);
  //  mass in electron volt
  float    weightEV(const uint8_t element);
  float    weightEV(const char * formula, const char * abbrev = NULL);

  //  CONVERSION
  float    moles2grams(const char * formula, float moles = 1.0);
  float    grams2moles(const char * formula, float grams = 1.0);
  float    dalton2EV(float Dalton);

  //  SPLIT FORMULA IN ELEMENTS
  uint8_t  splitElements(const char * formula);
  uint8_t  element(uint8_t element);


  //  COUNT
  //  if (element != NULL) count atoms of one element in a formula, e.g element == "H"
  //  if (element == NULL) count all atoms in the whole formula
  uint32_t count(const char * formula, const char * element = NULL);
  //  atom percentage of one element in a formula.
  float    atomPercentage(const char * formula, const char * element);


  //  DEBUG
  float   weightFactor();


private:
  uint8_t     _size;

  //  if (element == NULL) ==> whole weight otherwise only of element.
  float       _weight(char separator, const char * abbrev);
  float       _count(const char separator, const char * abbrev);
  char        *p;  //  for _weight() and _count()

  //  for splitElements
  uint8_t     _splitList[ATOMIC_WEIGHT_MAX_SPLIT_LIST]; //  default 20
  uint8_t     _found;
};


//  -- END OF FILE --

