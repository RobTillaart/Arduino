#pragma once
//
//    FILE: Adler16.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-06-15
// PURPOSE: Arduino Library for calculating Adler-16 checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32  
//          (no Adler16 reference, implementation is experimental)


#include "Arduino.h"


#define ADLER16_LIB_VERSION              (F("0.2.0"))


//  largest prime below 2^8
const uint16_t ADLER16_MOD_PRIME = 251;

class Adler16
{
public:
  Adler16();

  void begin(uint16_t s1 = 1, uint16_t s2 = 0);

  void add(uint8_t value);
  void add(uint8_t * array, uint16_t length);
  //  trade PROGMEM for speed
  void addFast(uint8_t * array, uint16_t length);

  //  wrappers for strings
  void add(char value);
  void add(char * array, uint16_t length);
  void addFast(char * array, uint16_t length);


  uint16_t getAdler();
  uint16_t count() { return _count; };

private:
  uint16_t _s1;
  uint16_t _s2;
  uint32_t _count;
};


// -- END OF FILE -- 


