//
//    FILE: fraction.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: library for fractions for Arduino
//     URL:
//
// Released to the public domain
//
// TODO
// - get math for negative fractions OK
// - divide by zero errors
// - test extensively
//
// 0.1.03 - added toDouble(), tested several fractionize() codes, bug fixes.
// 0.1.02 - faster fractionize code
// 0.1.01 - some fixes
// 0.1.00 - initial version

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
    n = p;
    d = q;
    simplify();
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
    // if (n >= d)
    // {

    // s += p.print(n/d, DEC);
    // s += p.print(".");
    // }

    // s += p.print(n%d, DEC);
    s += p.print(n, DEC);
    s += p.print('/');
    s += p.print(d, DEC);
    return s;
};

// EQUALITIES
bool Fraction::operator == (Fraction c)
{
    return (n * c.d) == (d * c.n);
}

bool Fraction::operator != (Fraction c)
{
    return (n * c.d) != (d * c.n);
}

bool Fraction::operator > (Fraction c)
{
    // TODO neg values
    return (n * c.d) > (d * c.n);
}

bool Fraction::operator >= (Fraction c)
{
    // TODO neg values
    return (n * c.d) >= (d * c.n);
}

bool Fraction::operator < (Fraction c)
{
    // TODO neg values
    return (n * c.d) < (d * c.n);
}

bool Fraction::operator <= (Fraction c)
{
    // TODO neg values
    return (n * c.d) <= (d * c.n);
}

// NEGATE
Fraction Fraction::operator - ()
{
    return Fraction(-n, d);
}

// BASIC MATH
Fraction Fraction::operator + (Fraction c)
{
    if (d == c.d) return Fraction(n + c.n, d);
    return Fraction(n*c.d + c.n*d, d * c.d);
}

Fraction Fraction::operator - (Fraction c)
{
    if (d == c.d) return Fraction(n - c.n, d);
    return Fraction(n*c.d - c.n*d, d * c.d);
}

Fraction Fraction::operator * (Fraction c)
{
    return Fraction(n * c.n, d * c.d);	
}

Fraction Fraction::operator / (Fraction c)
{
    // TODO test for zero division
    return Fraction(n * c.d, d * c.n);
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
    // TODO test for zero division
    n *= c.d;
    d *= c.n;
    simplify();
}

double Fraction::toDouble()
{
    double f = (1.0 * n) / d;
    return f;
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
    bool neg = (n < 0) != (d < 0);
    int32_t p = abs(n);
    int32_t q = abs(d);
    int32_t x = gcd(p,q);
    p = p/x;
    q = q/x;

    // denominator max 4 digits keeps mul and div simple
    while (q > 10000)
    {
        p = (p + 5)/10;
        q = (q + 5)/10;
        x = gcd(p, q);
        p = p/x;
        q = q/x;
    }
    n = (neg)?-p:p;
    d = q;
}

//////////////////////////////////////////////////////////////////////////////
// fractionize() is a core function to find the fraction representation
// PRE: 0 <= f < 1.0
//
// minimalistic is fast and small
//
// check for a discussion found later
// - http://mathforum.org/library/drmath/view/51886.html
// - http://www.gamedev.net/topic/354209-how-do-i-convert-a-decimal-to-a-fraction-in-c/
//


/*
// MINIMALISTIC
// (100x) micros()=51484
double Fraction::fractionize(double f)  // simple, small, 2nd fastest
{
    n = round(f * 10000);  // why not 1000000 ?
    d = 10000;
    simplify();
    return 0; // abs(f - this.toDouble());
}
*/

// LINEAR SEARCH
// (100x) micros()=51484
// slow but stable version
double Fraction::fractionize(double f)
{
    long nn = 1, dd = 1;

    float r = 1 / f;
    float delta = f * dd - nn;
    while (abs(delta) > 0.00001)
    {
        dd++;
        if (delta < 0)
        {
            nn++;
            dd = nn * r;
        }
        delta = f * dd - nn;
    }
    n = nn;
    d = dd;
    return delta;
}


/*
// LINEAR SEARCH (mirror optimized)
// (100x) micros()=51484
// slow but stable version
/*
double Fraction::fractionize(double f)
{
    long nn = 1, dd = 1;
    bool inverse = false;

    if (f > 0.5)
    {
        f = 1-f;
        inverse = true;
    }

    float r = 1 / f;
    float delta = f * dd - nn;
    while (abs(delta) > 0.00001 && (dd < 10000))
    {
        dd++;
        if (delta < 0)
        {
            nn++;
            dd = nn * r;
        }
        delta = f * dd - nn;
    }
    n = inverse?(dd - nn):nn;
    d = dd;
    return delta;
}
*/


// ADD BY DIGIT - does not find "magic fractions" e.g. pi = 355/113
// (100x) micros()=392620
/*
double Fraction::fractionize(double f)  // divide and conquer, simple, small, 2nd fastest
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
    return f;
}
*/


// Dr. Peterson
// - http://mathforum.org/library/drmath/view/51886.html
// (100x) micros()=94504
// showed errors around 0
// 4x faster!
/*
double Fraction::fractionize(double val)
{    // find nearest fraction
    double Precision = 0.000001;
    Fraction low(0, 1);             // "A" = 0/1
    Fraction high(1, 1);            // "B" = 1/1
    for (int i = 0; i < 100; ++i)
    {
        double testLow = low.d * val - low.n;
        double testHigh = high.n - high.d * val;
        if (testHigh < Precision * high.d)
        break; // high is answer
        if (testLow < Precision * low.d)
        {  // low is answer
            high = low;
            break;
        }
        if (i & 1)
        {  // odd step: add multiple of low to high
            double test = testHigh / testLow;
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
            double test = testLow / testHigh;
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
*/

// BINARY SEARCH
// - http://www.gamedev.net/topic/354209-how-do-i-convert-a-decimal-to-a-fraction-in-c/
// (100x) micros()=1292452
// slower
/*
double Fraction::fractionize(double value)  // size ok, too slow.
{
    int max_denominator = 10000;

    int low_n = 0;
    int low_d = 1;
    int high_n = 1;
    int high_d = 1;
    int mid_n;
    int mid_d;

    do
    {
        mid_n = low_n + high_n;
        mid_d = low_d + high_d;
        if ( mid_n < value * mid_d )
        {
            low_n = mid_n;
            low_d = mid_d;
            n = high_n;
            d = high_d;
        }
        else
        {
            high_n = mid_n;
            high_d = mid_d;
            n = low_n;
            d = low_d;
        }
    } while ( mid_d <= max_denominator );
    return 0;
}
*/

//
// END OF FILE
//