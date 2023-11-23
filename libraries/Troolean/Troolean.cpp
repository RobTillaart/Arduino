//
//    FILE: Troolean.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: Arduino Library for a three state logic data type supporting {true false unknown}
//     URL: https://github.com/RobTillaart/Troolean


#include "Troolean.h"


/////////////////////////////////////////////////////
//
//  PUBLIC
//
Troolean::Troolean()
{
  _value = -1;
}


Troolean::Troolean(const int8_t val)
{
  if (val == 0) _value = 0;
  else if (val == -1) _value = -1;
  else _value = 1;
}


Troolean::Troolean(const Troolean &t)
{
  _value = t._value;
}


//  PRINTING
size_t Troolean::printTo(Print& p) const
{
  size_t n = 0;
  if (_value == 0) n += p.print("false");
  else if (_value == -1) n += p.print("unknown");
  else n += p.print("true");
  return n;
};


//////////////////////////////////////////////////
//
//  EQUALITIES
//  t == t
//  f == f
//  u == u
//
bool Troolean::operator == (const Troolean &t)
{
  return (_value == t._value);
}


bool Troolean::operator == (const bool &b)
{
  if (_value == 0 && !b) return true;
  if (_value == 1 && b) return true;
  return false;
}


bool Troolean::operator == (const int &i)
{
  if (_value == 0  && i == 0) return true;
  if (_value == -1 && i == -1) return true;
  if (_value == 1  && i != 0 && i != -1) return true;
  return false;
}


bool Troolean::operator != (const Troolean &t)
{
  return (_value != t._value);
}


bool Troolean::operator != (const bool &b)
{
  if (_value == 0 && !b) return false;
  if (_value == 1 && b) return false;
  return true;
}


bool Troolean::operator != (const int &i)
{
  if (_value == 0  && i != 0) return true;
  if (_value == -1 && i != -1) return true;
  if (_value == 1  && (i == 0 || i == -1)) return true;
  return false;
}


Troolean::operator bool() const
{
  if (_value == 1) return true;
  if (_value == 0) return false;
  return false;
}


//////////////////////////////////////////////////////////
//
//  NEGATE
//  t -> f
//  f -> t
//  u -> u
//
Troolean Troolean::operator ! ()
{
  if (_value == -1) return Troolean(-1);
  if (_value == 1) return Troolean(0);
  return Troolean(1);
}


//////////////////////////////////////////////////////////
//
//  LOGICAL OPERATORS
//
Troolean Troolean::operator && (const Troolean &t)
{
  if (_value == 0 || t._value == 0) return Troolean(0);
  if (_value == -1 || t._value == -1) return Troolean(-1);
  return Troolean(1);
}


Troolean Troolean::operator && (const bool &b)
{
  if (_value == 0 || !b) return Troolean(0);
  if (_value == 1 && b) return Troolean(1);
  return Troolean(-1);
}


Troolean Troolean::operator || (const Troolean &t)
{
  if (_value == 1 || t._value == 1) return Troolean(1);
  if (_value == 0 && t._value == 0) return Troolean(0);
  return Troolean(-1);
}


Troolean Troolean::operator || (const bool &b)
{
  if (_value == 1 || b) return Troolean(1);
  if (_value == 0 && !b) return Troolean(0);
  return Troolean(-1);
}


bool Troolean::isTrue()
{
  return ((_value != 0) && (_value != -1));
}


bool Troolean::isFalse()
{
  return _value == 0;
}


bool Troolean::isUnknown()
{
  return _value == -1;
}


//  -- END OF FILE --

