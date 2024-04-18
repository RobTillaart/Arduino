#pragma once
//
//    FILE: float16.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library to implement float16 data type.
//          half-precision floating point format,
//          used for efficient storage and transport.
//     URL: https://github.com/RobTillaart/float16


#include "Arduino.h"

#define FLOAT16_LIB_VERSION                 (F("0.3.0"))


class float16
{
public:
  //  Constructors
  float16(void)               { _value = 0x0000; };
  float16(double f);
  float16(const float16 &f)   { _value = f._value; };

  //  Conversion and printing
  double   toDouble(void) const;
  float    toFloat() const;
  String   toString(unsigned int decimals = 2) const;  //  keep esp32 happy.

  //  access the 2 byte representation.
  uint16_t getBinary()           { return _value; };
  void     setBinary(uint16_t u) { _value = u; };

  //  equalities
  bool     operator == (const float16& f);
  bool     operator != (const float16& f);
  bool     operator >  (const float16& f);
  bool     operator >= (const float16& f);
  bool     operator <  (const float16& f);
  bool     operator <= (const float16& f);

  //  negation
  float16  operator - ();

  //  basic math
  float16  operator + (const float16& f);
  float16  operator - (const float16& f);
  float16  operator * (const float16& f);
  float16  operator / (const float16& f);

  float16& operator += (const float16& f);
  float16& operator -= (const float16& f);
  float16& operator *= (const float16& f);
  float16& operator /= (const float16& f);

  //  math helper functions
  int      sign();       //  1 = positive   0 = zero   -1 = negative.
  bool     isZero();
  bool     isNaN();
  bool     isInf();
  bool     isPosInf();
  bool     isNegInf();

  //  CORE CONVERSION
  //  should be private, needed for testing.
  float    f16tof32(uint16_t) const;
  uint16_t f32tof16(float) const;


private:
  uint16_t _value;

};


//  -- END OF FILE --

