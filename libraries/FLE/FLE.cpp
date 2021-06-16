//
//    FILE: FLE.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.2
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
//  HISTORY
//  0.0.1  2020-07-21  initial version
//  0.1.0  2020-12-23  arduino-CI + unit tests
//  0.1.1  2021-05-27  fix arduino-lint
//  0.1.2  2021-06-15  add negation + unit tests
//                     add first comparisons + some experimental
//


#include "FLE.h"


FLE::FLE(float val, float err)
{
  _v = val;
  _e = abs(err);
};


// PRINTABLE
size_t FLE::printTo(Print& p) const
{
  size_t n = 0;
  n += p.print(_v, _decimals);
  n += p.print(' ');
  n += p.print(_sep);
  n += p.print(' ');
  n += p.print(_e, _decimals);
  return n;
}


/////////////////////////////////////////////////
//
// MATH OPERATORS
//

// NEGATION
FLE FLE::operator - ()
{
  return FLE(-_v, _e);
}


FLE FLE::operator + (const FLE &in)
{
  return FLE(_v + in._v, _e + in._e);
}


// SUBTRACT
FLE FLE::operator - (const FLE &in)
{
  return FLE(_v - in._v, _e + in._e);
}


FLE FLE::operator * (const FLE &in)
{
  float val = _v * in._v;
  float err = (relError() + in.relError()) * val;
  return FLE(val, err);
}


FLE FLE::operator / (const FLE &in)
{
  float val = _v / in._v;
  float err = (relError() + in.relError()) * val;
  return FLE(val, err);
}


FLE FLE::operator += (const FLE &in)
{
  _v += in._v;
  _e += in._e;
  return *this;
}


FLE FLE::operator -= (const FLE &in)
{
  _v -= in._v;
  _e += in._e;
  return *this;
}


FLE FLE::operator *= (const FLE &in)
{
  float sum = relError() + in.relError();
  _v *= in._v;
  _e =  sum * _v;
  return *this;
}


FLE FLE::operator /= (const FLE &in)
{
  float sum = relError() + in.relError();
  _v /= in._v;
  _e =  sum * _v;
  return *this;
}


/////////////////////////////////////////////////
//
// BOOL OPERATORS
//
bool FLE::operator == (const FLE &in)
{
  return ((_v == in._v) && (_e == in._e));
}

bool FLE::operator != (const FLE &in)
{
  return ((_v != in._v) || (_e != in._e));
}

// bool FLE::operator >= (const FLE &in)
// {
  // return ((*this == in) || (low() >= in.high()));
// }

bool FLE::operator > (const FLE &in)
{
  return low() > in.high();
}


// bool FLE::operator <= (const FLE &in)
// {
  // return ((*this == in) || (high() <= in.low()) );
// }

bool FLE::operator < (const FLE &in)
{
  return high() < in.low();
}


/////////////////////////////////////////////////
//
// MISC OPERATORS
//
bool FLE::in(FLE a)
{
  return ( a.low() <= low() && high() <= a.high());
}



/////////////////////////////////////////////////
//
// EXPERIMENTAL
//
bool FLE::peq(const FLE &in)
{
  if (in.low() <= low() && in.high() >= low() ) return true;
  if (low() <= in.low() && high() >= in.low() ) return true;
  return false;
}

bool FLE::pne(const FLE &in)
{
  return !(*this == in);
}



// -- END OF FILE --
