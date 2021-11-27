//
//    FILE: float16.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: library for Float16s for Arduino
//     URL: http://en.wikipedia.org/wiki/Half-precision_floating-point_format
//
//  HISTORY:
//  0.1.00  2015-03-10  initial version
//  0.1.01  2015-03-12  make base conversion separate functions
//  0.1.02  2015-03-14  getting rounding right
//  0.1.03 
//  0.1.4   2021-11-26  setup repo to get it working again.
//                      still experimental.
//


#include "float16.h"

// #define DEBUG

// CONSTRUCTOR
float16::float16(double f)
{
    n = f32tof16(f);
}


// PRINTING
size_t float16::printTo(Print& p) const
{
    double d = this->f16tof32(n);
    return p.print(d, _decimals);
};


double float16::toDouble() const
{
    return f16tof32(n);
}


// NEGATE
float16 float16::operator - ()
{
    return float16( -f16tof32(n) );
}

//    bool float16::isNaN();
//    bool float16::isInf();


// EQUALITIES
bool float16::operator == (const float16 &f)
{
    return (n == f.n);
}


bool float16::operator != (const float16 &f)
{
    return (n != f.n);
}


bool float16::operator > (const float16 &c)
{
    return this->toDouble() > c.toDouble();
}


bool float16::operator >= (const float16 &c)
{
    return this->toDouble() >= c.toDouble();
}


bool float16::operator < (const float16 &c)
{
    return this->toDouble() < c.toDouble();
}


bool float16::operator <= (const float16 &c)
{
    return this->toDouble() <= c.toDouble();
}


/*
// BASIC MATH I
float16 float16::operator + (const float16 &c)
{
  return (float16(this->toDouble() + c.toDouble());
}

float16 float16::operator - (const float16 &c)
{
  return (float16(this->toDouble() - c.toDouble());
}

float16 float16::operator * (const float16 &c)
{
  return (float16(this->toDouble() * c.toDouble());
}

float16 float16::operator / (const float16 &c)
{
  return (float16(this->toDouble() / c.toDouble());
}
*/


/*
// BASIC MATH II
float16& float16::operator += (const float16 &c)
{
}

float16& float16::operator -= (const float16 &c)
{
}

float16& float16::operator *= (const float16 &c)
{
}

float16& float16::operator /= (const float16 &c)
{
}

*/


float float16::f16tof32(uint16_t n) const
{
    uint16_t sgn, man;
    int exp;
    double f;

    sgn = (n & 0x8000) > 0;
    exp = (n & 0x7C00) >> 10;
    man = (n & 0x03FF);

#ifdef DEBUG
    Serial.println(sgn, BIN);
    Serial.println(exp, BIN);
    Serial.println(man, BIN);
#endif

    // ZERO
    if ((n & 0x7FFF) == 0)
    {
#ifdef DEBUG
        Serial.println("ZERO");
#endif
        return sgn ? -0 : 0;
    }
    // NAN & INF
    if (exp == 0x001F)
    {
#ifdef DEBUG
        Serial.println("INFINITY");
#endif
        if (man == 0) return sgn ? -INFINITY : INFINITY;
        else return NAN;
    }

    // SUBNORMAL/NORMAL
    if (exp == 0)  f = 0;
    else           f = 1;

    // PROCESS MANTISSE
    for (int i = 9; i >= 0; i--)
    {
        f *= 2;
        if (man & (1 << i)) f = f + 1;
    }
    f = f * pow(2.0, exp - 25);
    if (exp == 0)
    {
        f = f * pow(2.0, -13);    // 5.96046447754e-8;
    }
    return sgn ? -f : f;
}


uint16_t float16::f32tof16(float f) const
{
    uint32_t t = *(uint32_t *) &f;
    // man bits = 10; but we keep 11 for rounding
    uint16_t man = (t & 0x007FFFFF) >> 12;
    int16_t  exp = (t & 0x7F800000) >> 23;
    bool     sgn = (t & 0x80000000);

    // Serial.print("SGN: "); Serial.println(sgn, BIN);
    // Serial.print("EXP: "); Serial.println(exp, BIN);
    // Serial.print("MAN: "); Serial.println(man, BIN);

    // handle 0
    if ((t & 0x7FFFFFFF) == 0)
    {
        return sgn ? 0x8000 : 0x0000;
    }
    // denormalized float32 does not fit in float16
    if (exp == 0x00)
    {
        return sgn ? 0x8000 : 0x0000;
    }
    // handle infinity & NAN
    if (exp == 0x00FF)
    {
        if (man) return 0xFE00;         //  NAN
        return sgn ? 0xFC00 : 0x7C00;   // -INF : INF
    }

    // normal numbers
    exp = exp - 127 + 15;
    // overflow does not fit => INF
    if (exp > 30) 
    {
        return sgn ? 0xFC00 : 0x7C00;   // -INF : INF
    }
    //  subnormal numbers
    if (exp < -38)
    {
        return sgn ? 0x8000 : 0x0000;  // -0 or 0  ?   just 0 ?
    }
    if (exp <= 0) // subnormal
    {
        man >>= (exp + 14);
        // rounding
        man++;
        man >>= 1;
        if (sgn) return 0x8000 | man;
        return man;
    }

    // normal
    // TODO rounding
    exp <<= 10;
    man++;
    man >>= 1;
    // Serial.print("SGN: "); Serial.println(sgn, BIN);
    // Serial.print("EXP: "); Serial.println(exp, BIN);
    // Serial.print("MAN: "); Serial.println(man, BIN);
    if (sgn) return 0x8000 | exp | man;
    return exp | man;
}


// -- END OF FILE --

