//
//    FILE: fraction.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: demo library for fractions for Arduino
//     URL:
//
// Released to the public domain
//

#ifndef Fraction_h
#define Fraction_h

#include "Arduino.h"

#define FRACTIONLIBVERSION "0.1.03"

class Fraction: public Printable
{
public:
    Fraction(double);
    Fraction(int32_t, int32_t);
    Fraction(int32_t);
    Fraction(int16_t);
    Fraction(int8_t);
    Fraction(const Fraction&);

    size_t printTo(Print& p) const;

    bool operator == (Fraction);
    bool operator != (Fraction);
    bool operator >  (Fraction);
    bool operator >= (Fraction);
    bool operator <  (Fraction);
    bool operator <= (Fraction);

    Fraction operator - (); // negation

    Fraction operator + (Fraction);
    Fraction operator - (Fraction);
    Fraction operator * (Fraction);
    Fraction operator / (Fraction);

    void operator += (Fraction);
    void operator -= (Fraction);
    void operator *= (Fraction);
    void operator /= (Fraction);

    double toDouble();

private:
    void simplify();
    double fractionize(double);
    int32_t gcd(int32_t, int32_t);

    int32_t n;
    int32_t d;
};

#endif
//
// -- END OF FILE --
//