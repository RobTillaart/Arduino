#pragma once
//
//    FILE: Soundex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
//    DATE: 2022-02-05
// PURPOSE: Arduino Library for calculating Soundex hash
//     URL: https://github.com/RobTillaart/Soundex


#include "Arduino.h"


#define SOUNDEX_LIB_VERSION              (F("0.1.5"))


#define SOUNDEX_MIN_LENGTH               4

#ifndef SOUNDEX_MAX_LENGTH
#define SOUNDEX_MAX_LENGTH               12
#endif


class Soundex
{
public:
  Soundex();

  void     setLength(uint8_t length = 4);
  uint8_t  getLength();

  char *   soundex(const char * str);       //  Russel and Odell
  uint16_t soundex16(const char * str);     //  Russel and Odell  length = 5
  uint32_t soundex32(const char * str);     //  Russel and Odell  length = 10


private:
  char     _buffer[SOUNDEX_MAX_LENGTH];
  uint8_t  _length;

  uint8_t sdx[26] = {0,1,2,3,0,1,2,0,0,2,2,4,5,5,0,1,2,6,2,3,0,1,0,2,0,2};
};


//  -- END OF FILE --

