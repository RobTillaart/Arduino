//
//    FILE: FLE.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
//  HISTORY
//  0.0.1  2020-07-21  initial version
//  0.1.0  2020-12-23  arduino-CI + unit tests


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

// TODO - initial implementation.
// TODO - test with negative values

FLE FLE::operator + (const FLE &in)
{
  return FLE(_v + in._v, _e + in._e);
}

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



// -- END OF FILE --

