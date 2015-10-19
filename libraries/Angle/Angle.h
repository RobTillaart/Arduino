#ifndef ANGLE_H
#define ANGLE_H
//
//    FILE: Angle.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.06
// PURPOSE: angle library for Arduino
// HISTORY: See angle.cpp
//
// Released to the public domain
//
// AngleFormat proxy added 03/03/15 by Christoper Andrews.
//

#include <math.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Printable.h"

#define ANGLE_LIB_VERSION "0.1.06"

class Angle;

enum AngleFormatMode{
    D = 1, M, S, T
};

struct AngleFormat : Printable{

    AngleFormat( const Angle &ref, AngleFormatMode format );
    size_t printTo(Print& p) const;

    const Angle &angle;
    AngleFormatMode mode;
};

class Angle: public Printable
{
public:
    Angle(int dd=0, int mm=0, int ss=0, int tt=0);
    Angle(double alpha);
    Angle(char * str);

    int sign()   { return neg?-1:1; };
    int degree() { return d; };
    int minute() { return m; };
    int second() { return s; };
    int tenthousand() { return t; };

    size_t printTo(Print& p) const { return printTo( p, T ); }
    size_t printTo(Print& p, AngleFormatMode mode) const;

    AngleFormat format( AngleFormatMode format ) { return AngleFormat( *this, format ); }

    double toDouble();
    double toRadians() { return toDouble() * PI / 180.0; };
    void fromRadians(double rad) { *this = rad * 180.0/PI; };

    // EQUALITIES
    bool operator == (const Angle& a) { return compare(*this, a) == 0; };
    bool operator != (const Angle& a) { return compare(*this, a) != 0; };
    bool operator <  (const Angle& a) { return compare(*this, a) <  0; };
    bool operator <= (const Angle& a) { return compare(*this, a) <= 0; };
    bool operator >  (const Angle& a) { return compare(*this, a) >  0; };
    bool operator >= (const Angle& a) { return compare(*this, a) >= 0; };

    // NEGATE
    Angle operator - ();

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

    Angle addHelper(const Angle &a);
    Angle subHelper(const Angle &a);

    bool neg; // angle is negative
    int d; // whole degrees
    int m; // minutes
    int s; // seconds
    int t; // tenhousands
};
#endif