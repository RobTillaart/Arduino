#pragma once
//
//    FILE: LUHN.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-24
// PURPOSE: Arduino Library for calculating LUHN checksum.
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"

#define LUHN_LIB_VERSION                      (F("0.1.0"))


class LUHN
{
public:
  LUHN();

  //        buffer == \0 terminated
  bool      isValid(const char * buffer);
  bool      isValid(char * buffer);
  char      generateChecksum(char * buffer);

  //  GENERATING AN ID
  void      randomize(uint32_t a, uint32_t b);
  bool      generate(char * buffer, uint8_t length, char * prefix);


protected:
  uint32_t  m_w = 1;  //  random generator parameter
  uint32_t  m_z = 2;  //  random generator parameter
  uint8_t   Marsaglia_mod10();
};


//  -- END OF FILE --

