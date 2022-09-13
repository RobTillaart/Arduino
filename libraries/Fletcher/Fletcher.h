#pragma once
//
//    FILE: Fletcher.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2022-01-25
// PURPOSE: Arduino Library for calculating Fletcher's checksum
//     URL: https://github.com/RobTillaart/Fletcher
//          https://en.wikipedia.org/wiki/Fletcher%27s_checksum


#include "Arduino.h"


#define FLETCHER_LIB_VERSION              (F("0.1.6"))

#define FLETCHER_16                       255
#define FLETCHER_32                       65535UL
#define FLETCHER_64                       4294967295ULL


//
//  straightforward implementation.
//  max length buffer 65534.
//  Wikipedia shows optimizations.
//
uint16_t fletcher16(uint8_t *data, uint16_t length);

uint32_t fletcher32(uint16_t *data, uint16_t length);

uint64_t fletcher64(uint32_t *data, uint16_t length);


// -- END OF FILE --

