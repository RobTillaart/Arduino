//
//    FILE: Angle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: library for Angle math for Arduino
//     URL: https://github.com/RobTillaart/Angle
//          http://forum.arduino.cc/index.php?topic=339402


#include "Angle.h"


AngleFormat::AngleFormat( const Angle &ref, AngleFormatMode format )
: angle(ref), mode(format)
{
}


size_t AngleFormat::printTo(Print& p) const
{
    return angle.printTo( p, mode );
}


Angle::Angle(int dd, int mm, int ss, int tt)
{
    _negative = false;
    _degrees = dd;
    _minutes = mm;
    _seconds = ss;
    _tenths  = tt;
    //  normalize();
    //  assume only one (largest) parameter is negative at most...
    if (_degrees < 0) { _degrees = -_degrees; _negative = true; }
    if (_minutes < 0) { _minutes = -_minutes; _negative = true; }
    if (_seconds < 0) { _seconds = -_seconds; _negative = true; }
    if (_tenths  < 0) { _tenths  = -_tenths ; _negative = true; }
    //  modulo might be faster
    while (_tenths >= 10000) { _seconds++; _tenths -= 10000; }
    while (_seconds >= 60)   { _minutes++; _seconds -= 60; }
    while (_minutes >= 60)   { _degrees++; _minutes -= 60; }
    //  check special case 0
    if (_degrees == 0 && _minutes == 0 && _seconds == 0 && _tenths == 0)
    {
      _negative = false;
    }
}


Angle::Angle(const double alpha)
{
    double angle = alpha;
    _negative = (alpha < 0);
    if (_negative) angle = -angle;

    _degrees = int(angle);
    angle = angle - _degrees;
    //  unsigned long p = angle * 3600000L;
    //  3600 000 = 2^7 • 3^2 • 5^5 = 128 * 28125
    //  2^7 = 128 will only affect exponent - no loss precision
    //  28125 is less digits so less loss of significant digits.
    //  upgraded to 4 decimal seconds
    //  36 000 000L = 256 * 140625
    angle = angle * 256;
    unsigned long p = round(angle * 140625.0);
    _tenths = p % 10000UL;
    p = p / 10000UL;
    _seconds = p % 60UL;
    _minutes = p / 60UL;
    //  check special case 0
    if (_degrees == 0 && _minutes == 0 && _seconds == 0 && _tenths == 0)
    {
      _negative = false;
    }
}


Angle::Angle(const char * str)
{
    uint32_t yy = 0;
    uint8_t decimals = 0;
    _negative = false;
    //  parse whole degrees
    char *p = (char *) str;
    _degrees = 0;
    //  skip crap
    while (!isdigit(*p) && (*p != '-')) p++;
    //  process sign
    if (*p == '-')
    {
        _negative = true;
        p++;
    }
    if (*p == '+') p++;
    //  parse whole part into degrees
    while (isdigit(*p))
    {
        _degrees *= 10;
        _degrees += (*p - '0');
        p++;
    }
    //  parse decimal part into an uint32_t
    if (*p != '\0')
    {
        p++;  // skip decimal point .
        while (isdigit(*p) && decimals < 9)
        {
            decimals++;
            yy *= 10;
            yy += (*p - '0');
            p++;
        }
    }
    //  make sure we have 9 decimal places.
    while (decimals < 9)
    {
        decimals++;
        yy *= 10;
    }
    //  convert float to degrees. 1000000000 ~> 36000000  -> /250 * 9
    //  yy = yy * 4 / 125 + yy / 250;  //  just keeps the maths within 32 bits
    yy = yy * 4 / 125;
    yy = yy + (yy + 4)/ 8;  //  just keeps the maths within 32 bits
    //  split yy in minutes, seconds, tenThousands
    _tenths = yy % 10000UL;
    yy = yy / 10000UL;
    _seconds = yy % 60;
    _minutes = yy / 60;
    //  check special case 0
    if (_degrees == 0 && _minutes == 0 && _seconds == 0 && _tenths == 0)
    {
      _negative = false;
    }
}


//  PRINTING
size_t Angle::printTo(Print& p, AngleFormatMode mode) const
{
    unsigned char c = mode;
    char separator[4] = ".\'\"";   //  "...";  //  ALT-0176 = °  179.59.59.9999

    size_t n = 0;
    if (_negative) n += p.print('-');
    n += p.print(_degrees);
    n += p.print(separator[0]);
    if( --c )
    {
        if (_minutes < 10) n += p.print('0');
        n += p.print(_minutes);
        n += p.print(separator[1]);
        if( --c )
        {
            if (_seconds < 10) n += p.print('0');
            n += p.print(_seconds);
            n += p.print(separator[2]);
            if( --c )
            {
                if (_tenths < 1000) n += p.print('0');
                if (_tenths < 100) n += p.print('0');
                if (_tenths < 10) n += p.print('0');
                n += p.print(_tenths);
            }
        }
    }
    return n;
};


double Angle::toDouble(void)
{
    long v = _tenths + _seconds * 10000UL + _minutes * 600000UL;
    double value = ((1.0 / 140625.0) / 256) * v + _degrees;
    if (_negative) value = -value;
    return value;
}


//  NEGATE
Angle Angle::operator - ()
{
    Angle temp = *this;
    if (temp._degrees == 0 && temp._minutes == 0 && temp._seconds == 0 && temp._tenths == 0)
    {
        temp._negative = false;
    }
    else
    {
        temp._negative = !_negative;
    }
    return temp;
};


//  BASIC MATH
Angle Angle::operator + (const Angle &a)    //  TOCHECK
{
    return addHelper(a);
}


Angle& Angle::operator += (const Angle &a)  //  TOCHECK
{
    *this = addHelper(a);
    return *this;
}


Angle Angle::addHelper(const Angle &a)      //  TOCHECK
{
    Angle temp = *this;
    if (temp._negative == a._negative)
    {
        temp._degrees += a._degrees;
        temp._minutes += a._minutes;
        temp._seconds += a._seconds;
        temp._tenths  += a._tenths ;
    }
    else
    {
        temp._degrees -= a._degrees;
        temp._minutes -= a._minutes;
        temp._seconds -= a._seconds;
        temp._tenths  -= a._tenths ;
    }
    temp.normalize();

    return temp;
}


Angle Angle::operator - (const Angle &a)    //  TOCHECK
{
    return subHelper(a);
}


Angle& Angle::operator -= (const Angle &a)  //  TOCHECK
{
    *this = subHelper(a);
    return *this;
}


Angle Angle::subHelper(const Angle &a)      //  TOCHECK
{
    Angle temp = *this;
    if (temp._negative == a._negative)
    {
        temp._degrees -= a._degrees;
        temp._minutes -= a._minutes;
        temp._seconds -= a._seconds;
        temp._tenths  -= a._tenths ;
    }
    else
    {
        temp._degrees += a._degrees;
        temp._minutes += a._minutes;
        temp._seconds += a._seconds;
        temp._tenths  += a._tenths ;
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


//  !! can divide by zero
double Angle::operator / (Angle& a)
{
    double f = this->toDouble();
    double g = a.toDouble();
    return f / g;
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//
int Angle::compare(const Angle &a, const Angle &b)
{
    //  check sign first
    if (!a._negative && b._negative) return 1;
    if (a._negative && !b._negative) return -1;
    //  check abs value
    int rv = 0;
    if (a._degrees > b._degrees) rv = 1;
    else if (a._degrees < b._degrees) rv = -1;
    else if (a._minutes > b._minutes) rv = 1;
    else if (a._minutes < b._minutes) rv = -1;
    else if (a._minutes > b._minutes) rv = 1;
    else if (a._minutes < b._minutes) rv = -1;
    else if (a._tenths > b._tenths) rv = 1;
    else if (a._tenths < b._tenths) rv = -1;

    if (rv != 0 && a._negative) rv = -rv;
    return rv;
}


void Angle::normalize()
{
    while (_tenths < 0)      { _seconds--; _tenths += 10000; }
    while (_tenths >= 10000) { _seconds++; _tenths -= 10000; }
    while (_seconds < 0)     { _minutes--; _seconds += 60; }
    while (_seconds >= 60)   { _minutes++; _seconds -= 60; }
    while (_minutes < 0)     { _degrees--; _minutes += 60; }
    while (_minutes >= 60)   { _degrees++; _minutes -= 60; }

    if (_degrees < 0)
    {
        if (_tenths != 0)
        {
            _tenths = 10000 - _tenths;
            _seconds++;
        }
        if (_seconds != 0)
        {
            _seconds = (60 - _seconds) % 60;
            _minutes++;
        }
        if (_minutes != 0)
        {
            _minutes = (60 - _minutes) % 60;
            _degrees++;
        }
        _degrees = -_degrees;
        _negative = !_negative;
    }

    if (_degrees == 0 && _minutes == 0 && _seconds == 0 && _tenths == 0)
    {
      _negative = false;
    }
}


// --- END OF FILE ---
