#pragma once
//
//    FILE: Angle.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: angle library for Arduino
//     URL: https://github.com/RobTillaart/Angle
//          http://forum.arduino.cc/index.php?topic=339402
//
// AngleFormat proxy added 03/03/15 by Christopher Andrews.


#include "math.h"
#include "Arduino.h"
#include "Printable.h"


#define ANGLE_LIB_VERSION               (F("0.2.0"))


class Angle;

enum AngleFormatMode
{
    D = 1, M, S, T
};


struct AngleFormat : Printable
{
    AngleFormat( const Angle &ref, AngleFormatMode format );
    size_t printTo(Print& p) const;

    const Angle &angle;
    AngleFormatMode mode;
};


class Angle: public Printable
{
public:
    Angle(int dd = 0, int mm = 0, int ss = 0, int tt = 0);
    Angle(double alpha);
    Angle(const char * str);

    int sign()        { return _negative ? -1 : 1; };
    int degree()      { return _degrees; };
    int minute()      { return _minutes; };
    int second()      { return _seconds; };
    int tenthousand() { return _tenths; };

    size_t printTo(Print& p) const { return printTo( p, T ); }
    size_t printTo(Print& p, AngleFormatMode mode) const;

    AngleFormat format( AngleFormatMode format ) { return AngleFormat( *this, format ); }

    double toDouble();
    double toRadians() { return toDouble() * (PI / 180.0); };
    void fromRadians(double radians) { *this = radians * (180.0 / PI); };

    //  EQUALITIES
    bool operator == (const Angle& a) { return compare(*this, a) == 0; };
    bool operator != (const Angle& a) { return compare(*this, a) != 0; };
    bool operator <  (const Angle& a) { return compare(*this, a) <  0; };
    bool operator <= (const Angle& a) { return compare(*this, a) <= 0; };
    bool operator >  (const Angle& a) { return compare(*this, a) >  0; };
    bool operator >= (const Angle& a) { return compare(*this, a) >= 0; };

    //  NEGATE
    Angle operator - ();

    Angle operator + (const Angle&);
    Angle& operator += (const Angle&);

    Angle operator - (const Angle&);
    Angle& operator -= (const Angle&);

    Angle operator * (const double);
    Angle& operator *= (const double);

    Angle operator / (const double);
    Angle& operator /= (const double);

    double operator / (Angle&);   //  ratio

private:
    void normalize();
    int compare(const Angle&, const Angle&);

    Angle addHelper(const Angle &a);
    Angle subHelper(const Angle &a);

    bool _negative;  //  angle is negative
    int  _degrees;
    int  _minutes;
    int  _seconds;
    int  _tenths;      //  ten thousands
};


//  -- END OF FILE

