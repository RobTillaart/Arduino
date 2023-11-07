#pragma once
//
//    FILE: integer24.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2023-06-22
// PURPOSE: Arduino library for the uint24_t and int24_t
//     URL: https://github.com/RobTillaart/integer24
//
//  uses a simple typedef
//  only tested on AVR for now


#define INTEGER24_LIB_VERSION             (F("0.1.2"))


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


/*
//  interface of the class, int24_t idem.
//  copied from float16()

class uint24_t : public Printable
{
public:
  // Constructors
  uint24_t(void)               { _value = 0; };
  uint24_t(double f);
  uint24_t(const uint24_t &f)  { _value = f._value; };

  //  equalities
  bool operator == (const uint24_t& f);
  bool operator != (const uint24_t& f);
  
  bool operator >  (const uint24_t& f);
  bool operator >= (const uint24_t& f);
  bool operator <  (const uint24_t& f);
  bool operator <= (const uint24_t& f);

  //  negation
  uint24_t operator - ();

  //  basic math
  uint24_t operator + (const uint24_t& f);
  uint24_t operator - (const uint24_t& f);
  uint24_t operator * (const uint24_t& f);
  uint24_t operator / (const uint24_t& f);
  
  uint24_t& operator += (const uint24_t& f);
  uint24_t& operator -= (const uint24_t& f);
  uint24_t& operator *= (const uint24_t& f);
  uint24_t& operator /= (const uint24_t& f);

  // Printable
  size_t   printTo(Print& p) const;

  private:
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
  uint24_t _value;
#else
  uint32_t _value;
#endif

}
*/


//  -- END OF FILE --

