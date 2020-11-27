#pragma once
//
//    FILE: Troolean.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino Library for a three state logic datatype supporting {true false unknown}
//     URL: https://github.com/RobTillaart/Troolean
//          https://en.wikipedia.org/wiki/Three-valued_logic
//          Kleene and Priest logics
//
// HISTORY:
// see Troolean.cpp file
//

#include "Arduino.h"
#include "Printable.h"

#define TROOLEAN_LIB_VERSION (F("0.1.3"))

#define unknown -1

class Troolean: public Printable
{
public:
  Troolean();
  Troolean(const int8_t);    // 0 = false, -1 = unknown anything else = true
  Troolean(const Troolean&);

  size_t printTo(Print&) const;

  bool operator == (const Troolean&);
  bool operator == (const bool&);
  bool operator == (const int&);
  bool operator != (const Troolean&);
  bool operator != (const bool&);
  bool operator != (const int&);

  operator bool() const;

  Troolean operator ! ();   // negation

  Troolean operator && (const Troolean&);
  Troolean operator && (const bool&);
  Troolean operator || (const Troolean&);
  Troolean operator || (const bool&);

  // faster than ==
  inline bool isTrue()    { return _value == 1; };
  inline bool isFalse()   { return _value == 0; };
  inline bool isUnknown() { return _value == -1; };

  // ideas
  // Troolean operator &&=
  // Troolean operator ||=
  //
  // bool toBool(); // returns random true/false if unknown....
  // extend with dontcare ?  ==> four state logic ?  Foolean?

private:
  int8_t _value;

};

// -- END OF FILE --
