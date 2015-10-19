//
//    FILE: Angle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.06
// PURPOSE: library for Angle math for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=339402

//
// Released to the public domain
//
// 0.1.06 - fixed bug negative values.
// 0.1.05 - added AngleFormat proxy added 03/03/15 by Christoper Andrews.
// 0.1.04 - changed thousands in tenthousands, string constructor
// 0.1.03 - added URL, fromRadians [TEST]
// 0.1.02 - added toRadians() + fix compare()
// 0.1.01 - cleanup a bit
// 0.1.00 - initial version

#include "Angle.h"

AngleFormat::AngleFormat( const Angle &ref, AngleFormatMode format )
: angle(ref), mode(format) {}

size_t AngleFormat::printTo(Print& p) const
{
    return angle.printTo( p, mode );
}

Angle::Angle(int dd, int mm, int ss, int tt) // todo optimize
{
    neg = false;
    d = dd;
    m = mm;
    s = ss;
    t = tt;
    // TODO
    // normalize();
    // assume only one param is neg at most...
    if (d < 0) { d = -d; neg = true; }
    if (m < 0) { m = -m; neg = true; }
    if (s < 0) { s = -s; neg = true; }
    if (t < 0) { t = -t; neg = true; }
    while (t >= 10000) { s++; t -= 10000; }
    while (s >= 60)    { m++; s -= 60; }
    while (m >= 60)    { d++; m -= 60; }
    if (d == 0 && m == 0 && s == 0 && t == 0) neg = false;
}

Angle::Angle(const double alpha)
{
    double a = alpha;
    neg = (alpha < 0);
    if (neg) a = -a;

    d = int(a);
    a = a - d;
    // unsigned long p = a * 3600000L;
    // 3600 000 = 2^7 • 3^2 • 5^5 = 128 * 28125
    // 2^7 = 128 will only affect exponent - no loss precision
    // 28125 is less digits so less loss of significant digits.
    // upgraded to 4 decimal seconds
    // 36 000 000L = 256 * 140625
    a = a * 256;
    unsigned long p = round(a * 140625.0);
    t = p % 10000UL;
    p = p / 10000UL;
    s = p % 60UL;
    m = p / 60UL;
}

Angle::Angle(char * str)
{
    uint32_t yy = 0;
    uint8_t d_cnt = 0;
    neg = false;
    // parse whole degrees
    char *p = str;
    d = 0;
    // skip crap
    while (!isdigit(*p) && (*p != '-')) p++;
    // process sign
    if (*p == '-')
    {
        neg = true;
        p++;
    }
    if (*p == '+') p++;
    // parse whole part into degrees;
    while (isdigit(*p))
    {
        d *= 10;
        d += (*p - '0');
        p++;
    }
    // parse decimal part into an uint32_t
    if (*p != '\0')
    {
        p++;  // skip .
        while (isdigit(*p) && d_cnt < 9)
        {
            d_cnt++;
            yy *= 10;
            yy += (*p - '0');
            p++;
        }
    }
    // make sure we have 9 decimal places.
    while (d_cnt < 9)
    {
        d_cnt++;
        yy *= 10;
    }
    // convert float to degrees. 1000000000 ~> 36000000  -> /250 * 9
    // yy = yy * 4 / 125 + yy / 250;  // just keeps the math within 32 bits
    yy = yy * 4 / 125;
    yy = yy + (yy + 4)/ 8;  // just keeps the math within 32 bits
    // split yy in m, s, tt
    t = yy % 10000UL;
    yy = yy / 10000UL;
    s = yy % 60;
    m = yy / 60;
}

// PRINTING
size_t Angle::printTo(Print& p, AngleFormatMode mode) const
{
    unsigned char c = mode;
    char separator[4] = ".\'\"";   // "...";  // ALT-0176 = °  179.59.59.9999

    size_t n = 0;
    if (neg) n += p.print('-');
    n += p.print(d);
    n += p.print(separator[0]);
    if( --c )
    {
        if (m < 10) n += p.print('0');
        n += p.print(m);
        n += p.print(separator[1]);
        if( --c )
        {
            if (s < 10) n += p.print('0');
            n += p.print(s);
            n += p.print(separator[2]);
            if( --c )
            {
                if (t < 1000) n += p.print('0');
                if (t < 100) n += p.print('0');
                if (t < 10) n += p.print('0');
                n += p.print(t);
            }
        }
    }
    return n;
};

double Angle::toDouble(void)
{
    long v = t + s * 10000UL + m * 600000UL;
    double val = ((1.0 / 140625.0) / 256) * v + d;
    if (neg) val = -val;
    return val;
}

// NEGATE
Angle Angle::operator - ()
{
    Angle temp = *this;
    if (temp.d == 0 && temp.m == 0 && temp.s == 0 && temp.t == 0)
    {
        temp.neg = false;
    }
    else
    {
        temp.neg = !neg;
    }
    return temp;
};

// BASIC MATH
Angle Angle::operator + (const Angle &a) // TOCHECK
{
    return addHelper(a);
}

Angle& Angle::operator += (const Angle &a) // TOCHECK
{
    *this = addHelper(a);
    return *this;
}

Angle Angle::addHelper(const Angle &a) // TOCHECK
{
    Angle temp = *this;
    if (temp.neg == a.neg)
    {
        temp.d += a.d;
        temp.m += a.m;
        temp.s += a.s;
        temp.t += a.t;
    }
    else
    {
        temp.d -= a.d;
        temp.m -= a.m;
        temp.s -= a.s;
        temp.t -= a.t;
    }
    temp.normalize();

    return temp;
}

Angle Angle::operator - (const Angle &a) // TOCHECK
{
    return subHelper(a);
}

Angle& Angle::operator -= (const Angle &a) // TOCHECK
{
    *this = subHelper(a);
    return *this;
}

Angle Angle::subHelper(const Angle &a) // TOCHECK
{
    Angle temp = *this;
    if (temp.neg == a.neg)
    {
        temp.d -= a.d;
        temp.m -= a.m;
        temp.s -= a.s;
        temp.t -= a.t;
    }
    else
    {
        temp.d += a.d;
        temp.m += a.m;
        temp.s += a.s;
        temp.t += a.t;
    }
    temp.normalize();
    return temp;
}

Angle Angle::operator * (const double dd)
{
    return Angle(this->toDouble() * dd);
}

Angle Angle::operator / (const double dd)
{
    return Angle(this->toDouble() / dd);
}

Angle& Angle::operator *= (const double dd)
{
    *this = this->toDouble() * dd;
    return *this;
}

Angle& Angle::operator /= (const double dd)
{
    *this = this->toDouble() / dd;
    return *this;
}

// !! can divide by zero
double Angle::operator / (Angle& a)
{
    double f = this->toDouble();
    double g = a.toDouble();
    return f/g;
}

///////////////////////////////////////////////////////////
//
// PRIVATE
//
int Angle::compare(const Angle &a, const Angle &b)
{
    // check sign first
    if (!a.neg && b.neg) return 1;
    if (a.neg && !b.neg) return -1;
    // check abs value
    int rv = 0;
    if (a.d > b.d) rv = 1;
    else if (a.d < b.d) rv = -1;
    else if (a.m > b.m) rv = 1;
    else if (a.m < b.m) rv = -1;
    else if (a.s > b.s) rv = 1;
    else if (a.s < b.s) rv = -1;
    else if (a.t > b.t) rv = 1;
    else if (a.t < b.t) rv = -1;

    if (rv != 0 && a.neg) rv = -rv;
    return rv;
}

void Angle::normalize()  // TOCHECK
{
    while (t < 0)      { s--; t += 10000; }
    while (t >= 10000) { s++; t -= 10000; }
    while (s < 0)      { m--; s += 60; }
    while (s >= 60)    { m++; s -= 60; }
    while (m < 0)      { d--; m += 60; }
    while (m >= 60)    { d++; m -= 60; }

    if (d < 0)
    {
        if (t != 0)
        {
            t = 10000 - t;
            s++;
        }
        if (s != 0)
        {
            s = (60 - s) % 60;
            m++;
        }
        if (m != 0)
        {
            m = (60 - m) % 60;
            d++;
        }
        d = -d;
        neg = !neg;
    }

    if (d == 0 && m == 0 && s == 0 && t == 0) neg = false;
}

// --- END OF FILE ---