#pragma once
//
//    FILE: Interval.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.4
// PURPOSE: Arduino library for Interval datatype
//     URL: https://github.com/RobTillaart/Interval


#include "Arduino.h"

#define INTERVAL_LIB_VERSION                (F("0.1.4"))

 
class Interval: public Printable
{
public:
  //  CONSTRUCTOR
  Interval();
  Interval(float lo, float hi);
  Interval(float f);             //  default zero interval [f, f]

  //  PRINTABLE
  size_t printTo(Print& p) const;
  void setDecimals(uint8_t n) { _decimals = n; };

  //  BASE FUNCTIONS
  float value()       { return (_hi /2 + _lo /2); };   //  assumption / estimation
  float range()       { return _hi -_lo; };
  float high()        { return _hi; };
  float low()         { return _lo; };
  float relAccuracy();
  void  setRange(float r);

  //  MATH OPERATORS
  Interval operator +  (const Interval&);
  Interval operator -  (const Interval&);
  Interval operator *  (const Interval&);
  Interval operator /  (const Interval&);
  Interval operator += (const Interval&);
  Interval operator -= (const Interval&);
  Interval operator *= (const Interval&);
  Interval operator /= (const Interval&);

  //  COMPARISON OPERATORS - compares value()
  bool operator == (const Interval&);
  bool operator != (const Interval&);
  // bool operator >  (const Interval&);
  // bool operator >= (const Interval&);
  // bool operator <  (const Interval&);
  // bool operator <= (const Interval&);


  //  SET OPERATORS
  // Interval operator  &  (const Interval&);  //  common part  [1, 5] & [4, 8] => [4, 5]
  // Interval operator  |  (const Interval&);  //  superset     [1, 5] | [4, 8] => [1, 8]
  // Interval operator  ^  (const Interval&);  // 
  //   smaller 

private:
  float   _lo;
  float   _hi;
  uint8_t _decimals = 3;
};


//  -- END OF FILE --

