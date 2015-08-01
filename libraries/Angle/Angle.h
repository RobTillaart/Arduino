#ifndef ANGLE_H
#define ANGLE_H
//
//    FILE: Angle.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.00
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

#define ANGLE_LIB_VERSION "0.1.00"

class Angle: public Printable
{
public:
    Angle(int dd=0, int mm=0, int ss=0, int tt =0) :
        d(dd), m(mm), s(ss), t(tt) 
        {
            normalize();
        }

    Angle(double alpha);
    
    int      degree()   { return d; };
    uint8_t  minute()   { return m; };
    uint8_t  second()   { return s; };
    uint16_t thousand() { return t; };

    size_t printTo(Print& p) const;
    double toDouble();

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
    void add(const Angle&);
    void sub(const Angle&);
    
    int d;
    int m;
    int s;
    int t;

};
#endif