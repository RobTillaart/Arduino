//
//    FILE: float16.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: library for Float16s for Arduino
//     URL: http://en.wikipedia.org/wiki/Half-precision_floating-point_format


#include "float16.h"


//  CONSTRUCTOR
float16::float16(double f)
{
  _value = f32tof16(f);
}


//////////////////////////////////////////////////////////
//
//  CONVERTING & PRINTING
//
double float16::toDouble() const
{
  return f16tof32(_value);
}

float float16::toFloat() const
{
  return f16tof32(_value);
}

String float16::toString(unsigned int decimals) const
{
  return String((double)f16tof32(_value), decimals);
}


//////////////////////////////////////////////////////////
//
//  EQUALITIES
//
bool float16::operator == (const float16 &f)
{
  return (_value == f._value);
}

bool float16::operator != (const float16 &f)
{
  return (_value != f._value);
}

bool float16::operator > (const float16 &f)
{
  if ((_value & 0x8000) && ( f._value & 0x8000)) return _value < f._value;
  if (_value & 0x8000) return false;
  if (f._value & 0x8000) return true;
  return _value > f._value;
}

bool float16::operator >= (const float16 &f)
{
  if ((_value & 0x8000) && (f._value & 0x8000)) return _value <= f._value;
  if (_value & 0x8000) return false;
  if (f._value & 0x8000) return true;
  return _value >= f._value;
}

bool float16::operator < (const float16 &f)
{
  if ((_value & 0x8000) && (f._value & 0x8000)) return _value > f._value;
  if (_value & 0x8000) return true;
  if (f._value & 0x8000) return false;
  return _value < f._value;
}

bool float16::operator <= (const float16 &f)
{
  if ((_value & 0x8000) && (f._value & 0x8000)) return _value >= f._value;
  if (_value   & 0x8000) return true;
  if (f._value & 0x8000) return false;
  return _value <= f._value;
}


//////////////////////////////////////////////////////////
//
//  NEGATION
//
float16 float16::operator - ()
{
  float16 f16;
  f16.setBinary(_value ^ 0x8000);
  return f16;
}


//////////////////////////////////////////////////////////
//
//  MATH
//
float16 float16::operator + (const float16 &f)
{
  return float16(this->toDouble() + f.toDouble());
}

float16 float16::operator - (const float16 &f)
{
  return float16(this->toDouble() - f.toDouble());
}

float16 float16::operator * (const float16 &f)
{
  return float16(this->toDouble() * f.toDouble());
}

float16 float16::operator / (const float16 &f)
{
  return float16(this->toDouble() / f.toDouble());
}

float16& float16::operator += (const float16 &f)
{
  *this = this->toDouble() + f.toDouble();
  return *this;
}

float16& float16::operator -= (const float16 &f)
{
  *this = this->toDouble() - f.toDouble();
  return *this;
}

float16& float16::operator *= (const float16 &f)
{
  *this = this->toDouble() * f.toDouble();
  return *this;
}

float16& float16::operator /= (const float16 &f)
{
  *this = this->toDouble() / f.toDouble();
  return *this;
}


//////////////////////////////////////////////////////////
//
//  MATH HELPER FUNCTIONS
//
int float16::sign()
{
  if (_value & 0x8000) return -1;
  if (_value & 0xFFFF) return 1;
  return 0;
}

bool float16::isZero()
{
  return ((_value & 0x7FFF) == 0x0000);
}

bool float16::isNaN()
{
  if ((_value & 0x7C00) != 0x7C00) return false;
  if ((_value & 0x03FF) == 0x0000) return false;
  return true;
}

bool float16::isInf()
{
  return ((_value == 0x7C00) || (_value == 0xFC00));
}

bool float16::isPosInf()
{
  return (_value == 0x7C00);
}

bool float16::isNegInf()
{
  return (_value == 0xFC00);
}


//////////////////////////////////////////////////////////
//
//  CORE CONVERSION
//
float float16::f16tof32(uint16_t _value) const
{
  uint16_t sgn, man;
  int exp;
  double f;

  sgn = (_value & 0x8000) > 0;
  exp = (_value & 0x7C00) >> 10;
  man = (_value & 0x03FF);

  //  ZERO
  if ((_value & 0x7FFF) == 0)
  {
    return sgn ? -0 : 0;
  }
  //  NAN & INF
  if (exp == 0x001F)
  {
    if (man == 0) return sgn ? -INFINITY : INFINITY;
    else return NAN;
  }

  //  NORMAL
  if (exp > 0)
  {
    f = pow(2.0, exp - 15) * (1 + man * 0.0009765625);
    return sgn ? -f : f;
  }
  //  SUBNORMAL
  //  exp == 0;
  f = pow(2.0, -24) * man;
  return sgn ? -f : f;
}


uint16_t float16::f32tof16(float f) const
{
  uint32_t t = *(uint32_t *) &f;
  //  man bits = 10; but we keep 11 for rounding
  uint16_t man = (t & 0x007FFFFF) >> 12;
  int16_t  exp = (t & 0x7F800000) >> 23;
  bool     sgn = (t & 0x80000000);

// Serial.print("BEFOR:\t ");
// Serial.print(sgn, HEX);
// Serial.print(" ");
// Serial.print(man, HEX);
// Serial.print(" ");
// Serial.println(exp, HEX);

  //  handle 0
  if ((t & 0x7FFFFFFF) == 0)
  {
    return sgn ? 0x8000 : 0x0000;
  }

  //  denormalized float32 does not fit in float16
  if (exp == 0x00)
  {
    return sgn ? 0x8000 : 0x0000;
  }

  //  handle INF and NAN == infinity and not a number
  if (exp == 0x00FF)
  {
    if (man) return 0xFE00;         //  NAN
    return sgn ? 0xFC00 : 0x7C00;   //  -INF : INF
  }

  //  rescale exponent
  exp = exp - 127 + 15;

  //  overflow does not fit => INF (infinity)
  if (exp > 30)
  {
    return sgn ? 0xFC00 : 0x7C00;   //  -INF : INF
  }

  //  subnormal numbers out of range => 0.
  if (exp < -9)
  {
    return sgn ? 0x8000 : 0x0000;   //  -0 or 0  ?   just 0 ?
  }

  //  subnormal numbers
  if (exp <= 0)
  {
    exp = 0;
    man = abs(f) * 16777216;  //  pow(2.0, 24);
    if (sgn) return 0x8000 | man;
    return man;
  }


  //  normal numbers
  //  rounding
  man++;
  man >>= 1;
  //  correction mantissa overflow issue #10
  if (man == 0x0400)
  {
    exp++;
    man = 0;
  }
  exp <<= 10;

// Serial.print("AFTER:\t ");
// Serial.print(sgn, HEX);
// Serial.print(" ");
// Serial.print(man, HEX);
// Serial.print(" ");
// Serial.println(exp, HEX);

  if (sgn) return 0x8000 | exp | man;
  return exp | man;
}


//  -- END OF FILE --

