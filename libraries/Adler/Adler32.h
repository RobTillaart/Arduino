#pragma once
//
//    FILE: Adler.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler-32 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32


#include "Arduino.h"


#define ADLER32_LIB_VERSION        (F("0.2.0"))


//  largest prime below 2^16
const uint32_t ADLER32_MOD_PRIME = 65521;


class Adler32
{
public:
  Adler32();

  void begin(uint32_t s1 = 1, uint32_t s2 = 0);

  void add(uint8_t value);
  void add(uint8_t * array, uint16_t length);
  //  trade PROGMEM for speed
  void addFast(uint8_t * array, uint16_t length);

  //  wrappers for strings
  void add(char value);
  void add(char * array, uint16_t length);
  void addFast(char * array, uint16_t length);


  uint32_t getAdler();
  uint32_t count() { return _count; };

private:
  uint32_t _s1;
  uint32_t _s2;
  uint32_t _count;
};


// -- END OF FILE -- 


