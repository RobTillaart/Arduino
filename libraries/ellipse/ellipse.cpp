//
//    FILE: ellipse.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// VERSION: 0.2.0
// PURPOSE: Arduino library for ellipse maths
//     URL: https://github.com/RobTillaart/ellipse
// TRIGGER: https://www.youtube.com/watch?v=5nW3nJhBHL0


#include "ellipse.h"


ellipse::ellipse(float a, float b)
{
  _a = abs(a);
  _b = abs(b);
}


//////////////////////////////////////////////////////////////////
//
//  unknown - see YouTube link.
//  p = 2 * PI * sqrt((a*a + b*b)/2);
//
float ellipse::circumference()
{
  return perimeter_Ramanujan1();
}


float ellipse::perimeter_reference()
{
  return perimeter_Ramanujan2();
}


float ellipse::perimeter_Kepler()
{
  //  Johannes Kepler (1571 - 1630)
  float p = 2 * PI * (_a + _b) / 2;   //  very fast for a ~ b
  return p;
}


float ellipse::perimeter_Ramanujan1()
{
  //  Srinivasa Ramanujan (1887-1920)
  //  algorithm I - very good
  //  float p = PI * (3 * (_a + _b) - sqrt((3 * _a +_b)*(_a + 3 * _b)));
  float a3 = 3 * _a;
  float b3 = 3 * _b;
  float p = PI * (a3 + b3 - sqrt( (a3 + _b)*(_a + b3)));
  //  one float operation less (~7% faster)
  return p;
}


float ellipse::perimeter_Parker()
{
  //  Matthew Parker, better than Ramanujan 1 for e > ~2.4
  //  not symmetric. _a should be longest.
  float a = (_a > _b) ? _a : _b;
  float b = (_a > _b) ? _b : _a;
  //  269 = prime 667 = 23*29  371 = 7*53
  float t = sqrt(269 * a * a + 667 * a * b + 371 * b * b);
  float p = PI * ((53.0/3.0) * a + (717.0/35.0) * b - t);
  return p;
}


float ellipse::perimeter_Ramanujan2()
{
  //  Srinivasa Ramanujan (1887-1920)
  //  algorithm II - extremely good
  float x = _a - _b;
  float y = _a + _b;
  float h3 = 3 * (x * x) / (y * y);
  float p = PI * y * ( 1 + h3 / (10 + sqrt(4 - h3)));
  return p;
}


//  optimized performance
float ellipse::perimeter_binomial()
{
  float x = _a - _b;
  float y = _a + _b;
  float h = (x * x) / (y * y);
  float hh = h;
  float p =  1 + hh * (1.0/4.0);
  hh *= h;  p += hh * (1.0/ 64.0);
  hh *= h;  p += hh * (1.0/ 256.0);
  hh *= h;  p += hh * (25.0/16384.0);
  hh *= h;  p += hh * (49.0/65536.0);
  hh *= h;  p += hh * (441.0/1048576.0);
  hh *= h;  p += hh * (1089.0/4194304.0);
  //  7 terms seems adequate for float precision.
  //  additional terms possible (see math is fun link),
  return p * PI * (_a + _b);
}


//  reference binomial()
// float ellipse::perimeter_binomial()
// {
  // float x = _a - _b;
  // float y = _a + _b;
  // float h = (x * x) / (y * y);
  // float p =  h /4 +
            // (h*h)/64 +
            // (h*h*h)/256 +
            // (25*h*h*h*h)/16384 +
            // (49*h*h*h*h*h)/65536 +
            // (441*h*h*h*h*h*h)/1048576 +
            // (1089*h*h*h*h*h*h*h)/4194304 +
            // 1;
  // return p * PI * (_a + _b);
// }


//  video @ 7:00
// float ellipse::perimeter_rough()
// {
  // //  fast, only for approximations.
  // //  error < 10% for b/a < 10.
  // float x = _a * _a + _b * _b;
  // float p = 2 * PI * sqrt(x / 2);
  // return p;
// }


//  video @ 12:00
float ellipse::perimeter_Parker_fast()
{
  //  fast, only for approximations.
  //  error < 5% for b/a < 75.
  float p = PI * ((6.0/5.0) * _a + (3.0/4.0) * _b);
  return p;
}


//  polynome order 2, approximation of Ramanujan.
//  assumes _b < _a.
float ellipse::perimeter_polynome()
{
  //  found with spreadsheet
  float p = 1.15106013377774;
  float q = 1.23383579382407;
  float r = 3.9344408776573;
  float ratio = _b / _a;
  float peri = _a * ((p * ratio + q) * ratio + r);
  return peri;
}


//////////////////////////////////////////////////////////

float ellipse::area()
{
  return PI * _a * _b;
}


float ellipse::eccentricity()
{
  if (_a == _b) return 0;  //  circle check
  if (_a ==  0) return 1;  //  DIV_ZERO check
  float x = _a * _a - _b * _b;
  if (x < 0) x = -x;
  return sqrt(x)/ _a;
  //  alternative formula has same nr of operator
  //  float x = sqrt(1 - (_b*_b)/(_a*_a));
}


float ellipse::ratio()
{
  if (_a == 0) return -1;
  return _b / _a;
}


bool ellipse::isCircle(float epsilon)
{
  if (epsilon == 0) return (_a == _b);
  float delta = abs(_a - _b);
  return (delta < epsilon);
}


bool ellipse::isFlat()
{
  if (_a > _b) return (_a > (4 * _b));
  return (_b > (4 * _a));
}


void ellipse::setA(float a)
{
  _a = abs(a);
}


void ellipse::setB(float b)
{
  _b = abs(b);
}


float ellipse::getA()
{
  return _a;
}


float ellipse::getB()
{
  return _b;
}


float ellipse::getC()
{
  float e = eccentricity();
  if (_a > _b) return e * _a;
  return e * _b;
}


float ellipse::getH()
{
  float u = _a - _b; u *= u;
  //  if (u == 0) return 0;
  float v = _a + _b; v *= v;
  return u / v;
}


float ellipse::getLongRadius()
{
  if (_a >= _b) return _a;
  return _b;
}


float ellipse::getShortRadius()
{
  if (_a >= _b) return _b;
  return _a;
}


float ellipse::angle()
{
  float c = (_b < _a) ? _b/_a : _a/_b;
  return acos(c) * (180 / PI);
}


//  -- END OF FILE --

