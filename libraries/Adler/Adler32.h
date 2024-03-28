#pragma once
//
//    FILE: Adler32.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.5
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32


#include "Arduino.h"


#define ADLER32_LIB_VERSION        (F("0.2.5"))


//  largest prime below 2^16
const uint32_t ADLER32_MOD_PRIME = 65521;


class Adler32
{
public:
  Adler32();

  void     begin(uint32_t s1 = 1, uint32_t s2 = 0);


  void     add(uint8_t value);
  //  returns current Adler value
  uint32_t add(uint8_t * array, uint16_t length);
  //  trade PROGMEM for speed
  //  returns current Adler value
  uint32_t addFast(uint8_t * array, uint16_t length);


  //  wrappers for char array's / strings
  void     add(char value);
  //  returns current Adler value
  uint32_t add(char * array, uint16_t length);
  //  returns current Adler value
  uint32_t addFast(char * array, uint16_t length);


  uint32_t getAdler();
  uint32_t count();


private:
  uint32_t _s1;
  uint32_t _s2;
  uint32_t _count;
};


//  -- END OF FILE --

