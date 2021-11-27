#pragma once
//
//    FILE: float16.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library to implement float16 data type.
//          half-precision floating point format, 
//          used for efficient storage and transport.
//     URL: https://github.com/RobTillaart/float16
//


#include "Arduino.h"

#define FLOAT16_LIB_VERSION "0.1.4"


class float16: public Printable
{
  public:
    // Constructors
    float16(void)               { n = 0; };
    float16(double f);
    float16(const float16 &f)   { n = f.n; };

    // Conversion
    double   toDouble(void) const;
    //  access the 2 byte representation.
    uint16_t getBinary()           { return n; };
    void     setBinary(uint16_t u) { n = u; };
    
    // Printable
    size_t   printTo(Print& p) const;
    void     setDecimals(uint8_t d) { _decimals = d; };
    uint8_t  getDecimals()          { return _decimals; };



//    bool isNaN();
//    bool isInf();


    // negation
    float16 operator - ();
    
    // equalities
    bool operator == (const float16&);
    bool operator != (const float16&);

    bool operator >  (const float16&);
    bool operator >= (const float16&);
    bool operator <  (const float16&);
    bool operator <= (const float16&);

    /*
    // basic math
    float16 operator + (const float16&);
    float16 operator - (const float16&);
    float16 operator * (const float16&);
    float16 operator / (const float16&);

    float16& operator += (const float16&);
    float16& operator -= (const float16&);
    float16& operator *= (const float16&);
    float16& operator /= (const float16&);
    */


    // DEBUGGING
    // should be private but for testing...
    float    f16tof32(uint16_t) const;
    uint16_t f32tof16(float) const;


  private:
    uint8_t  _decimals = 4;
    // TODO 
    // n is not descriptive, 
    // should be _n at least;
    uint16_t n;

};


// -- END OF FILE --

