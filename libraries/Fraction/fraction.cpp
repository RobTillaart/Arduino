//
//    FILE: fraction.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: library for fractions for Arduino
//     URL:
//
// Released to the public domain
//
// TODO
// - negative fractions
// - divide by zero errors
// - test extensively
// - better print output for whole numbers?

#include "fraction.h"

Fraction::Fraction(double f)
{
    if (f == 0.0)
    {
        n = 0;
        d = 1;
        return;
    }
    // Normalize
    bool neg = f < 0;
    if (neg) f = -f;
    bool rec = f > 1;
    if (rec) f = 1/f;

    fractionize(f);
    simplify();

    if (rec)
    {
        int32_t t = n;
        n = d;
        d = t;
    }
    if (neg) n = -n;
}

Fraction::Fraction(int32_t p, int32_t q)
{
    if (p == 0)
    {
        n = 0;
        d = 1;
        return;
    }
    n = abs(p);
    d = abs(q);
    simplify();
    // get sign right
    if ((p < 0) != (q < 0)) n = -n;
}

Fraction::Fraction(int32_t p)
{
    n = p;
    d = 1;
}

Fraction::Fraction(int16_t p)
{
    n = p;
    d = 1;
}

Fraction::Fraction(int8_t p)
{
    n = p;
    d = 1;
}

Fraction::Fraction(const Fraction &f)
{
    n = f.n;
    d = f.d;
}


// PRINTING
size_t Fraction::printTo(Print& p) const
{
    size_t s = 0;
    if (n >= d)
    {
        s += p.print(n/d, DEC);
        s += p.print(".");
    }
    s += p.print(n%d, DEC);
    s += p.print('/');
    s += p.print(d, DEC);
    return s;
};

// EQUALITIES
bool Fraction::operator == (Fraction c)
{
    return (n == c.n) && (d == c.d);
}

bool Fraction::operator != (Fraction c)
{
    return (n != c.n) || (d != c.d);
}

bool Fraction::operator > (Fraction c)
{
    return (n * c.d) > (d * c.n);
}

bool Fraction::operator >= (Fraction c)
{
    return (n * c.d) >= (d * c.n);
}

bool Fraction::operator < (Fraction c)
{
    return (n * c.d) < (d * c.n);
}

bool Fraction::operator <= (Fraction c)
{
    return (n * c.d) <= (d * c.n);
}

// NEGATE
Fraction Fraction::operator - ()
{
    return Fraction(-d, n);
}

// BASIC MATH
Fraction Fraction::operator + (Fraction c)
{
    if (d == c.d) return Fraction(n + c.n, d);
    int32_t dd = d * c.d;
    return Fraction(n*c.d + c.n*d, dd);
}

Fraction Fraction::operator - (Fraction c)
{
    if (d == c.d) return Fraction(n - c.n, d);
    int32_t dd = d * c.d;
    return Fraction(n*c.d - c.n*d, dd);
}

Fraction Fraction::operator * (Fraction c)
{
    return Fraction(n*c.n, d*c.d);	
}

Fraction Fraction::operator / (Fraction c)
{
    return Fraction(n*c.d, d*c.n);
}

void Fraction::operator += (Fraction c)
{
    if (d == c.d)
    {
        n += c.n;
        return;
    }
    n = n * c.d + c.n * d;
    d *= c.d;
    simplify();
}

void Fraction::operator -= (Fraction c)
{
    if (d == c.d)
    {
        n -= c.n;
        return;
    }
    n = n * c.d - c.n * d;
    d *= c.d;
    simplify();
}

void Fraction::operator *= (Fraction c)
{
    n *= c.n;
    d *= c.d;
    simplify();
}

void Fraction::operator /= (Fraction c)
{
    n *= c.d;
    d *= c.n;
    simplify();
}

// PRIVATE
int32_t Fraction::gcd(int32_t a , int32_t b)
{
    long c;
    while ( a != 0 )
    {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

// not that simple ...
void Fraction::simplify()
{
    int32_t x = gcd(n, d);
    n = n/x;
    d = d/x;
    // denominator max 4 digits
    while (d > 10000)
    {
        n = round(n * 0.1);
        d = round(d * 0.1);
        x = gcd(n, d);
        n = n/x;
        d = d/x;
    }
}

// fractionize() is a core function to find the fraction representation
// check for a discussion found later
// - http://mathforum.org/library/drmath/view/51886.html 
// - http://www.gamedev.net/topic/354209-how-do-i-convert-a-decimal-to-a-fraction-in-c/
//
// PRE: 0 <= f < 1.0
// slow but stable version, no divisions
// double Fraction::fractionize(double f)
// {
    // long nn = 1, dd = 1;

    // float r = 1 / f;
    // float delta = f * dd - nn;
    // while (abs(delta) > 0.00001)
    // {
        // dd++;
        // if (delta < 0)
        // {
            // nn++;
            // dd = nn * r;
        // }
        // delta = f * dd - nn;
    // }
    // n = nn;
    // d = dd;
    // return delta;
// }

double Fraction::fractionize(double f)
{
    Fraction t((long)0);
    for (long dd = 10; dd < 1000001; dd *= 10)
    {
        f *= 10;
        int ff = f;
        t += Fraction(ff, dd);
        f -= ff;
    }

    n = t.n;
    d = t.d;
    return 0;
}

//
// END OF FILE
//