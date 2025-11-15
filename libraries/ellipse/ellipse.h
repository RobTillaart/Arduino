#pragma once
//
//    FILE: ellipse.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// VERSION: 0.2.0
// PURPOSE: Arduino library for ellipse maths
//     URL: https://github.com/RobTillaart/ellipse


#include "Arduino.h"

#define ELLIPSE_LIB_VERSION           (F("0.2.0"))


class ellipse
{
public:
  ellipse(float a, float b);     //  a >= b
  float area();
  float circumference();         //  Ramanujan1

  float perimeter_reference();   //  Ramanujan2

  //  PERIMETER ALGORITHMS
  float perimeter_Kepler();      //  very fast, good for small eccentricity (< 0.5?)
  float perimeter_Ramanujan1();  //  fast, good
  float perimeter_Parker();      //  slow, good
  float perimeter_Ramanujan2();  //  slow, best over wide range
  float perimeter_binomial();    //  very slow, very good.

  //  not as good, mainly for approximations.
  //  error < 2.5% for a/b < 14
  //  error < 5%   for a/b < 75
  float perimeter_Parker_fast();  //  very fast
  //  error < 0.6%   for a/b < 20
  float perimeter_polynome();     //  very fast


  //  ATTRIBUTES
  float eccentricity();
  float ratio();
  //  convenience functions.
  bool  isCircle(float epsilon = 0.0);
  bool  isFlat();       //  factor 4 ==>  < 15°

  void  setA(float a);
  void  setB(float b);
  float getA();
  float getB();
  //  distance focal point from the centre
  float getC();
  //  often used (non physical) attribute
  float getH();

  float getLongRadius();
  float getShortRadius();

  //  EXPERIMENTAL
  //  returns the angle if the ellipse was the shadow of a circle.
  float angle();


private:
  float _a;
  float _b;
};


//  -- END OF FILE --


