//
//    FILE: Angle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.05
// PURPOSE: library for Angle math for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=339402

//
// Released to the public domain
//
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

Angle::Angle(const double alpha)
{
    double a = alpha;
    bool neg = (alpha < 0);
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

    if (neg) d = -d;
}

Angle::Angle(char * str)
{
    uint32_t yy = 0;
    uint8_t d_cnt = 0;
    bool neg = false;
    // parse whole degrees
    char *p = str;
    d = 0;
    while (!isdigit(*p) && (*p != '-')) p++;
    if (*p == '-')
    {
        neg = true;
        p++;
    }
    // parse whole part into degrees; assume +
    while (isdigit(*p))
    {
        d *= 10;
        d += (*p - '0');
        p++;
    }
    if (neg) d = -d;
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
    bool neg = false;
    if (d < 0)
    {
        neg = true;
        d = -d;
    }
    long v = t + s * 10000UL + m * 600000UL;

    double val = ((1.0 / 140625.0) / 256) * v + d;
    if (neg) val = -val;
    return val;
}

// BASIC MATH
Angle Angle::operator + (const Angle &a)
{
    return addHelper(a);
}

Angle& Angle::operator += (const Angle &a)
{
    *this = addHelper(a);
    return *this;
}

Angle Angle::addHelper(const Angle &a)
{
    Angle temp = *this;
    if (sign(temp.d) == sign(a.d))
    {
        temp.d += a.d;
        temp.m += a.m;
        temp.s += a.s;
        temp.t += a.t;
    }
    else
    {
        temp.d = sign(temp.d) * (abs(temp.d) - abs(a.d));
        temp.m -= a.m;
        temp.s -= a.s;
        temp.t -= a.t;
    }
    temp.normalize();
    return temp;
}

Angle Angle::operator - (const Angle &a)
{
    return subHelper(a);
}

Angle& Angle::operator -= (const Angle &a)
{
    *this = subHelper(a);
    return *this;
}

Angle Angle::subHelper(const Angle &a)
{
    Angle temp = *this;
    if (sign(temp.d) == sign(a.d))
    {
        temp.d -= a.d;
        temp.m -= a.m;
        temp.s -= a.s;
        temp.t -= a.t;
    }
    else
    {
        temp.d = sign(temp.d) * (abs(temp.d) + abs(a.d));
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
    if (a.d > b.d) return 1;
    if (a.d < b.d) return -1;
    if (a.m > b.m) return 1;
    if (a.m < b.m) return -1;
    if (a.s > b.s) return 1;
    if (a.s < b.s) return -1;
    if (a.t > b.t) return 1;
    if (a.t < b.t) return -1;
    return 0;
}

void Angle::normalize()
{
    bool neg = (d < 0);
    if (neg) d = -d;
    while (t < 0)      { s--; t += 10000; }
    while (t >= 10000) { s++; t -= 10000; }
    while (s < 0)      { m--; s += 60; }
    while (s >= 60)    { m++; s -= 60; }
    while (m < 0)      { d--; m += 60; }
    while (m >= 60)    { d++; m -= 60; }
    if (neg) d = -d;
}

int Angle::sign(int d)
{
    return (d < 0?-1:1);
}

// --- END OF FILE ---