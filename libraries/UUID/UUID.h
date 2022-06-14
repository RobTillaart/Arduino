#pragma once
//
//    FILE: UUID.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-06-14
// PURPOSE: Arduino Library for generating UUID's
//     URL: https://github.com/RobTillaart/UUID
//          https://en.wikipedia.org/wiki/UUID
//
// e.g. 20D24650-D900-E34F-DE49-8964AB3EB46D


#include "Arduino.h"
#include "Printable.h"


#define UUID_LIB_VERSION              (F("0.1.0"))


/////////////////////////////////////////////////
//
//  CLASS VERSION
//
class UUID : public Printable
{
public:
  UUID();

  //  at least one seed value is mandatory, two is better.
  void     seed(uint32_t s1, uint32_t s2 = 0);
  //  generate a new UUID
  void     generate();
  //  make a UUID string
  char *   toCharArray();

  //  Printable interface
  size_t   printTo(Print& p) const;


private:
  //  Marsaglia 'constants' + function
  uint32_t _m_w = 1;
  uint32_t _m_z = 2;
  uint32_t _random();

  //  UUID in string format
  char     _buffer[37];
};


// -- END OF FILE --

