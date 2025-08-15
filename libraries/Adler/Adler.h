#pragma once
//
//    FILE: Adler.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2022-01-27
// PURPOSE: Arduino Library for calculating Adler checksum
//     URL: https://github.com/RobTillaart/Adler
//          https://en.wikipedia.org/wiki/Adler-32


#include "Arduino.h"


#define ADLER_LIB_VERSION        (F("0.3.0"))


const uint64_t ADLER64_MOD_PRIME = 4294967291;
const uint32_t ADLER32_MOD_PRIME = 65521;
const uint16_t ADLER16_MOD_PRIME = 251;


/////////////////////////////////////////////////
//
//  STATIC FUNCTIONS
//
uint64_t adler64(uint8_t *data, uint16_t length, uint64_t s1 = 1, uint64_t s2 = 0);
uint32_t adler32(uint8_t *data, uint16_t length, uint32_t s1 = 1, uint32_t s2 = 0);
uint16_t adler16(uint8_t *data, uint16_t length, uint16_t s1 = 1, uint16_t s2 = 0);


//  char array wrappers
uint64_t adler64(char * array, uint16_t length, uint64_t s1 = 1, uint64_t s2 = 0);
uint32_t adler32(char * array, uint16_t length, uint32_t s1 = 1, uint32_t s2 = 0);
uint16_t adler16(char * array, uint16_t length, uint16_t s1 = 1, uint16_t s2 = 0);


//  -- END OF FILE --

