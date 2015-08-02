#ifndef ANGLE_H
#define ANGLE_H
//
//    FILE: Angle.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.02
// PURPOSE: angle library for Arduino
// HISTORY: See angle.cpp
//
// Released to the public domain
//

#include <math.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Printable.h"

#define ANGLE_LIB_VERSION "0.1.02"

class Angle: public Printable
{
public:
    Angle(int dd=0, int mm=0, int ss=0, int tt =0) :
    d(dd), m(mm), s(ss), t(tt)
    {
        normalize();
    }

    Angle(double alpha);

    int degree()   { return d; };
    int minute()   { return m; };
    int second()   { return s; };
    int thousand() { return t; };

    size_t printTo(Print& p) const;
    double toDouble();
    double toRadians() { return toDouble() * PI / 180.0; };

    // EQUALITIES
    bool operator == (const Angle& a) { return compare(*this, a) == 0; };
    bool operator != (const Angle& a) { return compare(*this, a) != 0; };
    bool operator <  (const Angle& a) { return compare(*this, a) <  0; };
    bool operator <= (const Angle& a) { return compare(*this, a) <= 0; };
    bool operator >  (const Angle& a) { return compare(*this, a) >  0; };
    bool operator >= (const Angle& a) { return compare(*this, a) >= 0; };

    // NEGATE
    Angle operator - () { return Angle(-d, m, s, t); };

    Angle operator + (const Angle&);
    Angle& operator += (const Angle&);

    Angle operator - (const Angle&);
    Angle& operator -= (const Angle&);

    Angle operator * (const double);
    Angle& operator *= (const double);

    Angle operator / (const double);
    Angle& operator /= (const double);

    double operator / (Angle&);   // ratio


private:
    void normalize();
    int compare(const Angle&, const Angle&);
    int sign(int);

    Angle addHelper(const Angle &a);
    Angle subHelper(const Angle &a);

    int d; // whole degrees
    int m; // minutes
    int s; // seconds
    int t; // thousands
};
#endif