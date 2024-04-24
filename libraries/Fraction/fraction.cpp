//
//    FILE: fraction.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library to implement a Fraction data type
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"


//////////////////////////////////////
//
//  CONSTRUCTORS
//
Fraction::Fraction(double d)
{
  Fraction::split(float(d));
}


Fraction::Fraction(float f)
{
  Fraction::split(f);
}


void Fraction::split(float f)
{
  //  handle special cases?
  //  PI = 355/113;      // 2.7e-7
  //  PI*2 = 710/113;
  //  PI/2 = 335/226;
  //  EULER = 2721/1001; // 1.1e-7
  //  EULER = 1264/465;  // 2.2e-6

  //  get robust for small values. (effectively zero)
  //  as 1/10000 is smallest
  if (abs(f) < 0.0001)
  {
    n = 0;
    d = 1;
    return;
  }
  if (int32_t(f) == f)
  {
    n = int32_t(f);
    d = 1;
    return;
  }

  //  handle sign
  bool negative = f < 0;
  if (negative) f = -f;

  //  strip of the integer part and process only remainder (0.0..1.0)
  int32_t integerPart = int32_t(f);  
  f = f - integerPart;

  fractionize(f);
  simplify();

  //  add integerPart again, but in units of denominator.
  n += (integerPart * d);
  if (negative)
  {
      n = -n;
  }
}


Fraction::Fraction(int32_t p, int32_t q) : n(p), d(q)
{
  simplify();
}



//////////////////////////////////////
//
//  EQUALITIES
//
bool Fraction::operator == (const Fraction &c)
{
  return (n * c.d) == (d * c.n);
}

// bool Fraction::operator == (const float &f)
// {
  // Fraction c(f);
    // return (n * c.d) == (d * c.n);
// }


bool Fraction::operator != (const Fraction &c)
{
  return (n * c.d) != (d * c.n);
}


bool Fraction::operator > (const Fraction &c)
{
  return (n * c.d) > (d * c.n);
}


bool Fraction::operator >= (const Fraction &c)
{
  return (n * c.d) >= (d * c.n);
}


bool Fraction::operator < (const Fraction &c)
{
  return (n * c.d) < (d * c.n);
}


bool Fraction::operator <= (const Fraction &c)
{
  return (n * c.d) <= (d * c.n);
}


//////////////////////////////////////
//
//  NEGATE
//
Fraction Fraction::operator - ()
{
  return Fraction(-n, d);
}


//////////////////////////////////////
//
//  BASIC MATH
//
Fraction Fraction::operator + (const Fraction &c)
{
  if (d == c.d)
  {
    return Fraction(n + c.n, d);
  }
  return Fraction(n*c.d + c.n*d, d * c.d);
}


Fraction Fraction::operator - (const Fraction &c)
{
  if (d == c.d)
  {
    return Fraction(n - c.n, d);
  }
  return Fraction(n*c.d - c.n*d, d * c.d);
}


Fraction Fraction::operator * (const Fraction &c)
{
  return Fraction(n * c.n, d * c.d);
}


Fraction Fraction::operator / (const Fraction &c)
{
  //  division by zero returns 0
  return Fraction(n * c.d, d * c.n);
}


Fraction& Fraction::operator += (const Fraction &c)
{
  if (d == c.d)
  {
    n += c.n;
  }
  else
  {
    n = n * c.d + c.n * d;
    d *= c.d;
  }
  simplify();
  return *this;
}


Fraction& Fraction::operator -= (const Fraction &c)
{
  if (d == c.d)
  {
    n -= c.n;
  }
  else
  {
    n = n * c.d - c.n * d;
    d *= c.d;
  }
  simplify();
  return *this;
}


Fraction& Fraction::operator *= (const Fraction &c)
{
  n *= c.n;
  d *= c.d;
  simplify();
  return *this;
}


Fraction& Fraction::operator /= (const Fraction &c)
{
  //  division by zero returns 0
  n *= c.d;
  d *= c.n;
  simplify();
  return *this;
}



//////////////////////////////////////
//
//  CONVERSION and PRINTING
//
double Fraction::toDouble()
{
  return double(n) / d;
}


float Fraction::toFloat()
{
  return float(n) / d;
}


String Fraction::toString()
{
  String s = "(";
  // if (n < 0) s += "-";
  s += n;
  s += "/";
  s += d;
  s += ")";
  return s;
}


//  fraction is proper if abs(fraction) < 1
bool Fraction::isProper()
{
  return abs(n) < abs(d);
}


//  fraction is proper if abs(fraction) < 1
bool Fraction::isInteger()
{
  return (d == 1);
}


//  visualize fraction as an angle in degrees
float Fraction::toAngle()
{
  return atan2(n, d) * (180.0 / PI);
}


int32_t Fraction::nominator()
{
  return n;
}


int32_t Fraction::denominator()
{
  return d;
}


//////////////////////////////////////
//
//  STATIC
//
// Mediant  - http://www.cut-the-knot.org/Curriculum/Arithmetic/FCExercise.shtml
// void Fraction::mediant(Fraction c)
// {
//   n += c.n;
//   d += c.d;
//   simplify();
// }
//

//  the mediant is a fraction that is always between 2 fractions
//  at least if within precision.
Fraction Fraction::mediant(const Fraction &a, const Fraction &b)
{
  return Fraction(a.n + b.n, a.d + b.d);
}


//  the middle is a fraction that is between 2 fractions
//  at least if within precision.
Fraction Fraction::middle(const Fraction &a, const Fraction &b)
{
  return Fraction(a.n*b.d + b.n*a.d, 2 * a.d * b.d);
}


//  approximate a fraction with defined denominator
//  sort of setDenominator(uint16_t den);
Fraction Fraction::setDenominator(const Fraction &a, uint16_t b)
{
  int32_t n = round((a.n * b * 1.0) / a.d);
  int32_t d = b;
  return Fraction(n, d);
}


//////////////////////////////////////
//
//  PROTECTED
//  http://en.wikipedia.org/wiki/Binary_GCD_algorithm
//
int32_t Fraction::gcd(int32_t a , int32_t b)
{
  while ( a != 0 )
  {
    int32_t c = a;
    a = b % a;
    b = c;
  }
  return b;
}


//  not that simple ...
void Fraction::simplify()
{
  if (n == 0)
  {
    d = 1;
    return;
  }
  bool neg = (n < 0) != (d < 0);
  int32_t p = abs(n);
  int32_t q = abs(d);
  int32_t x = gcd(p,q);
  p = p / x;
  q = q / x;

  //  denominator max 4 digits keeps mul and div simple
  //  in preventing overflow
  while (q > 10000)
  {
    //  rounding need improvement
    p = (p + 5)/10;
    q = (q + 5)/10;
    x = gcd(p, q);
    p = p / x;
    q = q / x;
  }
  n = (neg) ? -p : p;
  d = q;
}


//////////////////////////////////////////////////////////////////////////////
//
//  fractionize() - finds the fraction representation of a float
//  PRE: 0 <= f < 1.0
//
//  minimalistic, fast and small accuracy ~1e-4
// void Fraction::fractionize(float val)
// {
  // n = round(val * 9900);
  // d = 9900;
// }


//
//  check for a discussion found later (link is dead)
//  - http://mathforum.org/library/drmath/view/51886.html
//  - http://www.gamedev.net/topic/354209-how-do-i-convert-a-decimal-to-a-fraction-in-c/
//


//  Dr. Peterson
//  - http://mathforum.org/library/drmath/view/51886.html
//  (100x) micros()=96048
//  showed errors for very small values around 0


void Fraction::fractionize(float val)
{
  //  find nearest fraction
  float Precision = 0.0000001;
  //  Fraction low(int(val * 9900), 9900);             // "A" = 0/1
  //  Fraction high(int(val * 9240) + 1, 9240);            // "B" = 1/1
  Fraction low(0, 1);             // "A" = 0/1
  Fraction high(1, 1);            // "B" = 1/1

  //  max 100 iterations
  for (int i = 0; i < 100; ++i)
  {
    float testLow = low.d * val - low.n;
    float testHigh = high.n - high.d * val;
    if (testHigh < Precision * high.d)
    break;  //  high is answer

    if (testLow < Precision * low.d)
    {  //  low is answer
      high = low;
      break;
    }
    if (i & 1)
    {  //  odd step: add multiple of low to high
      float test = testHigh / testLow;
      int32_t count = (int32_t)test;    //  "N"
      int32_t n = (count + 1) * low.n + high.n;
      int32_t d = (count + 1) * low.d + high.d;
      if ((n > 0x8000) || (d > 0x10000))   //   0x8000 0x10000
      break;
      high.n = n - low.n;  //  new "A"
      high.d = d - low.d;
      low.n = n;           //  new "B"
      low.d = d;
    }
    else
    {   //  even step: add multiple of high to low
      float test = testLow / testHigh;
      int32_t count = (int32_t)test;     //  "N"
      int32_t n = low.n + (count + 1) * high.n;
      int32_t d = low.d + (count + 1) * high.d;
      if ((n > 0x10000) || (d > 0x10000))   //   0x10000 0x10000
      break;
      low.n = n - high.n;  //  new "A"
      low.d = d - high.d;
      high.n = n;          //  new "B"
      high.d = d;
    }
  }
  n = high.n;
  d = high.d;
}


//  -- END OF FILE --

