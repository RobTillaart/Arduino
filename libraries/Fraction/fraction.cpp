//
//    FILE: fraction.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.11
// PURPOSE: Arduino library to implement a Fraction datatype
//     URL: https://github.com/RobTillaart/Fraction
//
//
// TODO
// - divide by zero errors
// - test extensively
//
// 0.1.11   2020-12-23  arduino-CI + unit tests
// 0.1.10   2020-06-10  fix library.json
// 0.1.9    refactor
// 0.1.8    refactor made constructors explicit; fix issue #33 double --> float
// 0.1.07   major refactoring by Chris-A
// 0.1.06   added proper(), mediant(), angle();
// 0.1.05   tested negative Fractions math, added constructors,
//          minor refactoring,
// 0.1.04   stabilizing code, add simplify() for some code paths.
// 0.1.03   added toDouble(), tested several fractionize() codes, bug fixes.
// 0.1.02   faster fractionize code
// 0.1.01   some fixes
// 0.1.00   initial version

#include "fraction.h"

//////////////////////////////////////
//
// CONSTRUCTORS
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
    // handle special cases?
    // PI = 355/113;      // 2.7e-7
    // PI*2 = 710/113;
    // PI/2 = 335/226;
    // EULER = 2721/1001; // 1.1e-7
    // EULER = 1264/465;  // 2.2e-6

    // get robust for small values. (effectively zero)
    if (abs(f) < 0.00001)
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
    // Normalize to 0.0 ... 1.0
    bool negative = f < 0;
    if (negative) f = -f;
 
// TODO investigate different strategy:
// intpart = int32_t(f);   // strip of the integer part.
// f = f - intpart;        // determine remainder
// determine n, d
// n += intpart * d;       // add integer part * denominator to fraction.
 
    bool reciproke = f > 1;
    if (reciproke) f = 1/f;

    fractionize(f);
    simplify();

    // denormalize
    if (reciproke)
    {
        int32_t t = n;
        n = d;
        d = t;
    }
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
// PRINTING
//
size_t Fraction::printTo(Print& p) const
{
    size_t s = 0;
    // TODO split of sign first
    //
    //  vs 22/7 => 3_1/7
    // if (n >= d)
    // {
    // s += p.print(n/d, DEC);
    // s += p.print("_");
    // }
    // s += p.print(n%d, DEC);
    s += p.print(n, DEC);
    s += p.print('/');
    s += p.print(d, DEC);
    return s;
};

//////////////////////////////////////
//
// EQUALITIES
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
// NEGATE
//
Fraction Fraction::operator - ()
{
    return Fraction(-n, d);
}

//////////////////////////////////////
//
// BASIC MATH
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
    // division by zero returns 0
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
    // division by zero returns 0
    n *= c.d;
    d *= c.n;
    simplify();
    return *this;
}

float Fraction::toDouble()
{
    return (1.0 * n) / d;
}

// fraction is proper if abs(fraction) < 1
bool Fraction::isProper()
{
    return abs(n) < abs(d);
}

// visualize fraction as an angle in degrees
float Fraction::toAngle()
{
    return atan2(n, d) * 180.0 / PI;
}


//////////////////////////////////////
//
// STATIC
//
// Mediant  - http://www.cut-the-knot.org/Curriculum/Arithmetic/FCExercise.shtml
// void Fraction::mediant(Fraction c)
// {
//   n += c.n;
//   d += c.d;
//   simplify();
// }
//

// the mediant is a fraction that is always between 2 fractions
// at least if within precission.
Fraction Fraction::mediant(const Fraction &a, const Fraction &b)
{
    return Fraction(a.n + b.n, a.d + b.d);
}

// the middle is a fraction that is between 2 fractions
// at least if within precission.
Fraction Fraction::middle(const Fraction &a, const Fraction &b)
{
    return Fraction(a.n*b.d + b.n*a.d, 2 * a.d * b.d);
}

// approximate a fraction with defined denominator
// sort of setDenominator(uint16_t den);
Fraction Fraction::setDenominator(const Fraction &a, uint16_t b)
{
    int32_t n = round((a.n * b * 1.0) / a.d);
    int32_t d = b;
    return Fraction(n, d);
}


//////////////////////////////////////
//
// PRIVATE
// http://en.wikipedia.org/wiki/Binary_GCD_algorithm
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

// not that simple ...
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

    // denominator max 4 digits keeps mul and div simple
    // in preventing overflow
    while (q > 10000)
    {
        // rounding might need improvement
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
// fractionize() - finds the fraction representation of a float
// PRE: 0 <= f < 1.0
//
// minimalistic is fast and small
//
// check for a discussion found later
// - http://mathforum.org/library/drmath/view/51886.html
// - http://www.gamedev.net/topic/354209-how-do-i-convert-a-decimal-to-a-fraction-in-c/
//


// Dr. Peterson
// - http://mathforum.org/library/drmath/view/51886.html
// (100x) micros()=96048
// showed errors for very small values around 0
void Fraction::fractionize(float val)
{   
    // find nearest fraction
    float Precision = 0.0000001;
    Fraction low(0, 1);             // "A" = 0/1
    Fraction high(1, 1);            // "B" = 1/1
    for (int i = 0; i < 100; ++i)
    {
        float testLow = low.d * val - low.n;
        float testHigh = high.n - high.d * val;
        if (testHigh < Precision * high.d)
        break; // high is answer
        if (testLow < Precision * low.d)
        {  // low is answer
            high = low;
            break;
        }
        if (i & 1)
        {  // odd step: add multiple of low to high
            float test = testHigh / testLow;
            int32_t count = (int32_t)test;    // "N"
            int32_t n = (count + 1) * low.n + high.n;
            int32_t d = (count + 1) * low.d + high.d;
            if ((n > 0x8000) || (d > 0x10000))
            break;
            high.n = n - low.n;  // new "A"
            high.d = d - low.d;
            low.n = n;           // new "B"
            low.d = d;
        }
        else
        {  // even step: add multiple of high to low
            float test = testLow / testHigh;
            int32_t count = (int32_t)test;     // "N"
            int32_t n = low.n + (count + 1) * high.n;
            int32_t d = low.d + (count + 1) * high.d;
            if ((n > 0x10000) || (d > 0x10000))
            break;
            low.n = n - high.n;  // new "A"
            low.d = d - high.d;
            high.n = n;          // new "B"
            high.d = d;
        }
    }
    n = high.n;
    d = high.d;
}

// -- END OF FILE --
