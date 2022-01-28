#pragma once
//
//    FILE: ellipse.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// VERSION: 0.1.0
// PURPOSE: Arduino library for ellipse maths
//     URL: https://github.com/RobTillaart/ellipse
//


#include "Arduino.h"

#define ELLIPSE_LIB_VERSION           (F("0.1.0"))


class ellipse
{
public:
  ellipse(float a, float b);      // a >= b 
  float area();
  float circumference();    // good algorithm, 
  float perimeter_ref();    // pretty slow but very good over long range
  float perimeter_Keppler();
  float perimeter_Ramanujan1();
  float perimeter_Ramanujan2();
  float eccentricity();

  void  setA(float a) { _a = abs(a); };
  void  setB(float b) { _b = abs(b); };
  float getA()  { return _a; };
  float getB()  { return _b; };
  float getC();

private:
  float _a;
  float _b;
};


// -- END OF FILE --


