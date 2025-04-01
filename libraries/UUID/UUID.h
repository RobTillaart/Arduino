#pragma once
//
//    FILE: UUID.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/Universally_unique_identifier
//
// e.g.     20d24650-d900-e34f-de49-8964ab3eb46d


#include "Arduino.h"
#include "Printable.h"


#define UUID_LIB_VERSION              (F("0.2.0"))

//  TODO an enum?
const uint8_t UUID_MODE_RANDOM   = 0;
const uint8_t UUID_MODE_VERSION4 = 4;  //  replaces VARIANT4
const uint8_t UUID_MODE_VERSION8 = 8;  //  not supported yet


/////////////////////////////////////////////////
//
//  CLASS VERSION
//
class UUID : public Printable
{
public:
  //  seeds the UUID instance with compile time constants
  //  plus the micros() value as run time component
  //  to be fairly random for every instance.
  UUID();

  //  at least one seed value is mandatory, two is better.
  //  seed can be random or explicitly fixed.
  void     seed(uint32_t s1, uint32_t s2 = 0);
  //  void     autoSeed();  //  TODO experimental

  //  generate a new UUID
  void     generate();
  //  make a UUID string
  char *   toCharArray();

  //  MODE
  void     setRandomMode();
  void     setVersion4Mode();
  //  void     setVersion8Mode(uint8_t nodeId[6]);
  int      getMode();

  //  Printable interface
  size_t   printTo(Print& p) const;

  //  will be removed in 0.3.0
  [[deprecated("Use setVersion4Mode() instead")]]
  void     setVariant4Mode();


private:
  //  Marsaglia 'constants' + function
  uint32_t _m_w = 1;
  uint32_t _m_z = 2;
  uint32_t _random();
  uint32_t _hash(const char * str);

  //  UUID in string format
  char     _buffer[37];
  //  default mode.
  int      _mode = UUID_MODE_VERSION4;
};


//////////////////////////////////////////////////
//
//  DERIVED CLASS GUID
//
class GUID : public UUID
{
public:
  GUID();
};


//  -- END OF FILE --

