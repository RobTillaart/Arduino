//
//    FILE: Interval.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.4
// PURPOSE: Arduino library for Interval data type
//     URL: https://github.com/RobTillaart/Interval


#include "Interval.h"


Interval::Interval(float lo, float hi)
{
  if (lo <= hi)
  {
    _lo = lo;
    _hi = hi;
  }
  else
  {
  _lo = hi;
  _hi = lo;
  }
};


Interval::Interval(float f)
{
  _lo = f;
  _hi = f;
};


Interval::Interval()
{
  _lo = 0;
  _hi = 0;
};


float Interval::relAccuracy()
{
  if (value() == 0.0) return -1;
  return abs(range() / value());  //  TODO /2 ?
}


void Interval::setRange(float r)
{
  float f = value();
  _lo = f - r / 2;
  _hi = f + r / 2;
}


//  PRINTABLE
size_t Interval::printTo(Print& p) const
{
  size_t n = 0;
  n += p.print('[');
  n += p.print(_lo, _decimals);
  n += p.print(", ");
  n += p.print(_hi, _decimals);
  n += p.print(']');
  return n;
};


/////////////////////////////////////////////////
//
//  MATH BASIC OPERATIONS
//
Interval Interval::operator + (const Interval &in)
{
  return Interval(_lo + in._lo, _hi + in._hi);
}


Interval Interval::operator - (const Interval &in)
{
  return Interval(_lo - in._hi, _hi - in._lo);
}


Interval Interval::operator * (const Interval &in)
{
  return Interval(_lo * in._lo, _hi * in._hi);
}


Interval Interval::operator / (const Interval &in)
{
  return Interval(_lo / in._hi, _hi / in._lo);
}


Interval Interval::operator += (const Interval &in)
{
  _lo += in._lo;
  _hi += in._hi;
  return *this;
}


Interval Interval::operator -= (const Interval &in)
{
  _lo -= in._hi;
  _hi -= in._lo;
  return *this;
}


Interval Interval::operator *= (const Interval &in)
{
  _lo *= in._lo;
  _hi *= in._hi;
  return *this;
}


Interval Interval::operator /= (const Interval &in)
{
  _lo /= in._hi;
  _hi /= in._lo;
  return *this;
}


/////////////////////////////////////////////////
//
//  COMPARISON OPERATIONS
//

bool Interval::operator == (const Interval &in)
{
  return ((_lo == in._lo) && (_hi == in._hi));
}


bool Interval::operator != (const Interval &in)
{
  return ((_lo != in._lo) || (_hi != in._hi));
}

//  VALUE FOR NOW...
// bool Interval::operator >  (const Interval &in)
// {
//   return this->value() > in.value();
// }
//
// bool Interval::operator >= (const Interval &in)
// {
//   return this->value() >= in.value();
// }
//
// bool Interval::operator <  (const Interval &in)
// {
//   return this->value() < in.value();
// }
//
// bool Interval::operator <= (const Interval &in)
// {
//   return this->value() <= in.value();
// }


//  -- END OF FILE --

