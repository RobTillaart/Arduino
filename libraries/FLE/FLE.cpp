//
//    FILE: FLE.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.4
// PURPOSE: Arduino library for float with error data type
//     URL: https://github.com/RobTillaart/FLE


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
//  MATH OPERATORS
//

//  NEGATION
FLE FLE::operator - ()
{
  return FLE(-_v, _e);
}


FLE FLE::operator + (const FLE &in)
{
  return FLE(_v + in._v, _e + in._e);
}


//  SUBTRACT
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
//  BOOL OPERATORS
//
//  bool FLE::operator == (const FLE in)
//  {
//    return ((_v == in._v) && (_e == in._e));
//  }

bool FLE::operator == (const FLE &in)
{
  return ((_v == in._v) && (_e == in._e));
}

bool FLE::operator != (const FLE &in)
{
  return ((_v != in._v) || (_e != in._e));
}

//  bool FLE::operator >= (const FLE &in)
//  {
//    return ((*this == in) || (low() >= in.high()));
//  }

bool FLE::operator > (const FLE &in)
{
  return low() > in.high();
}


//  bool FLE::operator <= (const FLE &in)
//  {
//    return ((*this == in) || (high() <= in.low()) );
//  }

bool FLE::operator < (const FLE &in)
{
  return high() < in.low();
}


/////////////////////////////////////////////////
//
//  MISC OPERATORS
//
bool FLE::in(FLE a)
{
  return ( a.low() <= low() && high() <= a.high());
}


FLE FLE::shared(FLE a)
{
  float v, e;
  //  six possible cases.
  //  case 1, 6
  if ((*this < a) || (*this > a)) return FLE(NAN, NAN);  // no overlap

  //  case 3, 4
  if (a.in(*this)) return a;
  if (this->in(a)) return *this;

  //  case 2
  if (low() < a.low())
  {
    v = (a.low() + high())/2;
    e = v - a.low();
  }
  //  case 5
  else
  {
    v = (low() + a.high())/2;
    e = v - low();
  }
  return FLE(v, e);
}


FLE FLE::lower(FLE a)
{
  return FLE(0,0);   //  TODO
}


FLE FLE::higher(FLE a)
{
  return FLE(0,0);   //  TODO
}


/////////////////////////////////////////////////
//
//  WEAK PROPOSITIONS    TODO  elaborate
//
//  possible equal
bool FLE::peq(const FLE &a)
{
  if (a.low() <= low() && a.high() >= low() ) return true;
  if (low() <= a.low() && high() >= a.low() ) return true;
  return false;
}

//  possible not equal
bool FLE::pne(const FLE &a)
{
  return !(*this == a);
}

//  possible less than
bool FLE::plt(const FLE &a)
{
  return (this->low() < a.low());  // TODO
}

//  possible less equal
bool FLE::ple(const FLE &a)
{
  return (this->low() <= a.low());  // TODO
}

//  possible greater than
bool FLE::pgt(const FLE &a)
{
  return (this->high() > a.high());
}

//  possible greater equal
bool FLE::pge(const FLE &a)
{
  return (this->high() >= a.high());  // TODO
}



//  -- END OF FILE --
