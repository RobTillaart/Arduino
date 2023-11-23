#pragma once
//
//    FILE: Troolean.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: Arduino Library for a three state logic data type supporting {true false unknown}
//     URL: https://github.com/RobTillaart/Troolean
//          https://en.wikipedia.org/wiki/Three-valued_logic
//          Kleene and Priest logics


#include "Arduino.h"
#include "Printable.h"


#define TROOLEAN_LIB_VERSION            (F("0.1.8"))

//  VALUE     MEANING
//      0  =  false
//     -1  =  unknown
//  other  =  true
#define unknown                         -1


class Troolean: public Printable
{
public:
  Troolean();
  Troolean(const int8_t);       //  0 = false, -1 = unknown anything else = true
  Troolean(const Troolean&);

  //  PRINTING
  size_t printTo(Print&) const;

  //  EQUALITIES
  bool operator == (const Troolean&);
  bool operator == (const bool&);
  bool operator == (const int&);
  bool operator != (const Troolean&);
  bool operator != (const bool&);
  bool operator != (const int&);

  operator bool() const;

  //  NEGATE
  Troolean operator ! ();  //  not, negate

  //  LOGICAL OPERATORS
  Troolean operator && (const Troolean&);
  Troolean operator && (const bool&);
  Troolean operator || (const Troolean&);
  Troolean operator || (const bool&);

  bool isTrue();
  bool isFalse();
  bool isUnknown();


private:
  int8_t _value;

};


//  -- END OF FILE --

