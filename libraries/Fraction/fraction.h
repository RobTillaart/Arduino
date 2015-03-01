//
//    FILE: fraction.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.06
// PURPOSE: demo library for fractions for Arduino
//     URL:
//
// Released to the public domain
//

#ifndef Fraction_h
#define Fraction_h

#include "Arduino.h"

#define FRACTIONLIBVERSION "0.1.06"

class Fraction: public Printable
{
public:
    Fraction(double);
    Fraction(int32_t, int32_t);
    Fraction(int32_t);
    Fraction(int16_t);
    Fraction(int8_t);
    Fraction(uint32_t);
    Fraction(uint16_t);
    Fraction(uint8_t);
    Fraction(const Fraction&);

    size_t printTo(Print& p) const;

    // equalities
    bool operator == (Fraction);
    bool operator != (Fraction);
    bool operator >  (Fraction);
    bool operator >= (Fraction);
    bool operator <  (Fraction);
    bool operator <= (Fraction);

    // negation
    Fraction operator - ();

    // basic math
    Fraction operator + (Fraction);
    Fraction operator - (Fraction);
    Fraction operator * (Fraction);
    Fraction operator / (Fraction);

    void operator += (Fraction);
    void operator -= (Fraction);
    void operator *= (Fraction);
    void operator /= (Fraction);

    double toDouble();
    bool isProper();    // abs(f) < 1
    double toAngle();

    static Fraction mediant(Fraction, Fraction);
    // approximate a fraction with defined denominator
    static Fraction setDenominator(Fraction, uint16_t);


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