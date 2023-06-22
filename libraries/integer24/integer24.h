#pragma once
//
//    FILE: integer24.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-06-22
// PURPOSE: Arduino library for the uint24_t and int24_t
//     URL: https://github.com/RobTillaart/integer24
//
//  uses a simple typedef


#define INTEGER24_LIB_VERSION             (F("0.1.0"))


#include "Arduino.h"


#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

//  supports a true 3 byte data type

typedef __uint24  uint24_t;
typedef __int24   int24_t;

#else
  
//  use 32 bits (4 byte) for now

typedef uint32_t  uint24_t;
typedef int32_t   int24_t;

#endif


//  -- END OF FILE --

