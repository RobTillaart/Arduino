#pragma once
//
//    FILE: FLE.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.2
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
// HISTORY:
// see FLE.cpp file


#include "Arduino.h"
#include "math.h"

#define FLE_LIB_VERSION      (F("0.1.2"))


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
  FLE operator -  ();  // negation  c = -a;

  FLE operator +  (const FLE&);
  FLE operator -  (const FLE&);  // minus  c = a - b;
  FLE operator *  (const FLE&);
  FLE operator /  (const FLE&);
  FLE operator += (const FLE&);
  FLE operator -= (const FLE&);
  FLE operator *= (const FLE&);
  FLE operator /= (const FLE&);


  // BOOL OPERATORS
  //  for all value pairs of a and b
  bool operator == (const FLE&);
  bool operator != (const FLE&);
  bool operator >  (const FLE&);
  bool operator <  (const FLE&);


  // MISC OPERATORS
  //  FLE lies completely in range a
  //  meaning FLE is more precise than a => smaller error.
  bool in(FLE a);



  // EXPERIMENTAL - INVESTIGATE
  //

  //  weak propositions.
  bool peq (const FLE&);      // possible equal 
  bool pne (const FLE&);      // possible not equal

  // SET LIKE MATH
  FLE shared(FLE b);      // overlap.



  //  semantic meaning not 100% clear
  //  bool operator >= (const FLE&);
  //  bool operator <= (const FLE&);


  // bool plt (const FLE&);  // possible less than
  // bool ple (const FLE&);  // possible less equal
  // bool pgt (const FLE&);  // possible greater than
  // bool pge (const FLE&);  // possible greater equal



  // SET LIKE MATH
  // FLE shared(FLE a, FLE b);      // overlap.
  // FLE lower(FLE a, FLE b);     // part of a lower than b;
  // FLE higher(FLE a, FLE b);    // part of a higher than b;

  // float both%(FLE a, FLE b);   // overlap percentage
  // float sub%(FLE a, FLE b);    // part of a lower than b;
  // float sup%(FLE a, FLE b);    // part of a higher than b;

  // 
  //
  // infinite ?
  // NAN ?


  private:
  float   _v;
  float   _e;
  uint8_t _decimals = 2;
  char    _sep = '~';   //  _sep = '±';  // gives warning.
};


// -- END OF FILE --
