#pragma once
//
//    FILE: ellipse.h
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// VERSION: 0.1.4
// PURPOSE: Arduino library for ellipse maths
//     URL: https://github.com/RobTillaart/ellipse


#include "Arduino.h"

#define ELLIPSE_LIB_VERSION           (F("0.1.4"))


class ellipse
{
public:
  ellipse(float a, float b);      //  a >= b
  float area();
  float circumference();    //  good algorithm,

  float perimeter_ref();    //  pretty slow but very good over long range
  float perimeter_Keppler();
  float perimeter_Ramanujan1();
  float perimeter_Parker();
  float perimeter_Ramanujan2();

  float eccentricity();


  //  convenience functions.
  bool  isCircle(float epsilon = 0.0);
  bool  isFlat();       //  factor 4 ==>  < 15°

  void  setA(float a);  //  uses abs(a)
  void  setB(float b);  //  uses abs(b)
  float getA();
  float getB();
  float getC();

  float getLongRadius();
  float getShortRadius();

  //  experimental
  //  returns the angle if the ellipse was the shadow of a circle.
  float angle();

private:
  float _a;
  float _b;
};


//  -- END OF FILE --


