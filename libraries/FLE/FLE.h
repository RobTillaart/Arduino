#pragma once
//
//    FILE: FLE.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
// HISTORY:
// see FLE.cpp file


#include "Arduino.h"
#include "math.h"

#define FLE_LIB_VERSION      "0.1.0"
 
class FLE: public Printable
{
  public:
  // CONSTRUCTOR
  FLE(float val = 0, float error = 0);

  // PRINTABLE
  size_t printTo(Print& p) const;
  FLE    setDecimals(uint8_t n) { _decimals = n;  return *this; };
  FLE    setSeparator(char c)   { _sep = c; return *this; };

  // BASE FUNCTIONS
  float value()    const{ return _v; };
  float error()    const{ return _e; };
  float relError() const{ return (_v == 0 ? 0 : abs(_e / _v)); };
  float high()     const{ return _v + _e; };
  float low()      const{ return _v - _e; };

  // MATH OPERATORS
  FLE operator +  (const FLE&);
  FLE operator -  (const FLE&);
  FLE operator *  (const FLE&);
  FLE operator /  (const FLE&);
  FLE operator += (const FLE&);
  FLE operator -= (const FLE&);
  FLE operator *= (const FLE&);
  FLE operator /= (const FLE&);

  // BOOL OPERATORS

  private:
  float   _v;
  float   _e;
  uint8_t _decimals = 2;
  char    _sep = '±';
};


// -- END OF FILE --
