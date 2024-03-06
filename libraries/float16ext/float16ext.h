#pragma once
//
//    FILE: float16ext.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library to implement float16ext data type.
//          half-precision floating point format,
//          used for efficient storage and transport.
//     URL: https://github.com/RobTillaart/float16ext


#include "Arduino.h"

#define FLOAT16EXT_LIB_VERSION                 (F("0.1.0"))


class float16ext: public Printable
{
public:
  //  Constructors
  float16ext(void)                { _value = 0x0000; };
  float16ext(double f);
  float16ext(const float16ext &f) { _value = f._value; };

  //  Conversion
  double   toDouble(void) const;
  //  access the 2 byte representation.
  uint16_t getBinary()            { return _value; };
  void     setBinary(uint16_t u)  { _value = u; };

  //  Printable
  size_t   printTo(Print& p) const;
  void     setDecimals(uint8_t d) { _decimals = d; };
  uint8_t  getDecimals()          { return _decimals; };

  //  equalities
  bool     operator == (const float16ext& f);
  bool     operator != (const float16ext& f);

  bool     operator >  (const float16ext& f);
  bool     operator >= (const float16ext& f);
  bool     operator <  (const float16ext& f);
  bool     operator <= (const float16ext& f);

  //  negation
  float16ext  operator - ();

  //  basic math
  float16ext  operator + (const float16ext& f);
  float16ext  operator - (const float16ext& f);
  float16ext  operator * (const float16ext& f);
  float16ext  operator / (const float16ext& f);

  float16ext& operator += (const float16ext& f);
  float16ext& operator -= (const float16ext& f);
  float16ext& operator *= (const float16ext& f);
  float16ext& operator /= (const float16ext& f);

  //  math helper functions
  int      sign();       //  1 = positive   0 = zero   -1 = negative.
  bool     isZero();


  //  CORE CONVERSION
  //  should be private but for testing...
  float    f16tof32(uint16_t) const;
  uint16_t f32tof16(float) const;


private:
  uint8_t  _decimals = 4;
  uint16_t _value;

};


//  -- END OF FILE --

