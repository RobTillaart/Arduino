//
//    FILE: IEEE754tools.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: IEEE754 tools
//
// http://playground.arduino.cc//Main/IEEE754tools
//
// Released to the public domain
// not tested, use with care
//

#ifndef IEEE754tools_h
#define IEEE754tools_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// (un)comment lines to configure functionality / size
//#define IEEE754_ENABLE_MSB
#define IEEE754_ENABLE_DUMP

// IEEE754 float layout; 
struct IEEEfloat
{
    uint32_t m:23; 
    uint8_t e:8;
    uint8_t s:1;
};

// IEEE754 double layout; 
struct IEEEdouble
{
    uint64_t m:52; 
    uint16_t e:11;
    uint8_t s:1;
};

// Arduino UNO double layout: 
// the UNO has no 64 bit double, it is only able to map 23 bits of the mantisse
// a filler is added.
struct _DBL
{
    uint32_t filler:29;
    uint32_t m:23;
    uint16_t e:11;
    uint8_t  s:1;
};

// for packing and unpacking a float
typedef union _FLOATCONV
{
    IEEEfloat p;
    float f;
    byte b[4];
} _FLOATCONV;

// for packing and unpacking a double
typedef union _DBLCONV
{
    // IEEEdouble p;
    _DBL p;
    double d;           // !! is a 32bit float for UNO.
    byte b[4];
} _DBLCONV;


#ifdef IEEE754_ENABLE_DUMP
// print float components
void dumpFloat(float number)
{
    IEEEfloat* x = (IEEEfloat*) ((void*)&number);
    Serial.print(x->s, HEX);
    Serial.print("\t");
    Serial.print(x->e, HEX);
    Serial.print("\t");
    Serial.println(x->m, HEX);
    
    // Serial.print(" sign: "); Serial.print(x->s);
    // Serial.print("  exp: "); Serial.print(x->e);
    // Serial.print(" mant: "); Serial.println(x->m);
}

// print "double" components
void dumpDBL(struct _DBL dbl)
{
    Serial.print(dbl.s, HEX);
    Serial.print("\t");
    Serial.print(dbl.e, HEX);
    Serial.print("\t");
    Serial.println(dbl.m, HEX);
}
#endif


//
// converts a float to a packed array of 8 bytes representing a 64 bit double
// restriction exponent and mantisse.
//
// float;  array of 8 bytes;  LSBFIRST; MSBFIRST
//
void float2DoublePacked(float number, byte* bar, int byteOrder=LSBFIRST)  
{
    _FLOATCONV fl;
    fl.f = number;
    _DBLCONV dbl;
    dbl.p.s = fl.p.s;
    dbl.p.e = fl.p.e-127 +1023;  // exponent adjust
    dbl.p.m = fl.p.m;
    
#ifdef IEEE754_ENABLE_MSB
    if (byteOrder == LSBFIRST)
    {
#endif
        for (int i=0; i<8; i++)
        {
            bar[i] = dbl.b[i];
        }
#ifdef IEEE754_ENABLE_MSB
    }
    else
    {
        for (int i=0; i<8; i++)
        {
            bar[i] = dbl.b[7-i];
        }
    }
#endif
}

//
// converts a packed array of bytes into a 32bit float.
// there can be an exponent overflow
// the mantisse is truncated to 23 bits.
//
float doublePacked2Float(byte* bar, int byteOrder=LSBFIRST)
{
    _FLOATCONV fl;
    _DBLCONV dbl;
    
#ifdef IEEE754_ENABLE_MSB
    if (byteOrder == LSBFIRST)
    {
#endif
        for (int i=0; i<8; i++)
        {
            dbl.b[i] = bar[i];
        }
#ifdef IEEE754_ENABLE_MSB
    }
    else
    {
        for (int i=0; i<8; i++)
        {
            dbl.b[i] = bar[7-i];
        }
    }
#endif
    
    int e = dbl.p.e-1023+127;  // exponent adjust 
    // TODO check exponent overflow.
    if (e >=0 || e <= 255) 
    {
        fl.p.s = dbl.p.s;
        fl.p.e = e;  
        fl.p.m = dbl.p.m;  // note this one clips the mantisse 
    }
    else fl.f = NAN;
    
    return fl.f;
}

//
// NOT TESTED FUNCTIONS
// 
uint8_t getSign(float number)
{
  IEEEfloat* x = (IEEEfloat*) ((void*)&number);
  return x->s;
}

int getExponent(float number)
{
  IEEEfloat* x = (IEEEfloat*) ((void*)&number);
  return x->e - 127;
}

uint32_t getMantisse(float number)
{
  IEEEfloat* x = (IEEEfloat*) ((void*)&number);
  return x->m;
}

/*
// ONELINERS to speed up some specific 32 bit float math

// *(((byte*) &number)+3) &= 0x7F;              // number == fabs(number);
// x = *(((byte*) &number)+3) & 0x7F;           // x = fabs(number);
// GAIN = factor 2

// *(((byte*) &number)+3) |= 0x80;              // number == fabs(number);
// x = *(((byte*) &number)+3) | 0x80;           // x == -fabs(number);
// GAIN = factor 2

// *(((byte*) &number)+3) ^= 0x80;              // number = -number;
// x = *(((byte*) &number)+3) ^ 0x80;           // x = -number;
// GAIN = factor 2

// s = *(((uint8_t*) &number)+3) & 0x80;        // s = sign(number);
// if ( *(((byte*) &number)+3) & 0x80) x=2;     // if (number < 0) x=2;
// GAIN = factor 5

int getExponent(float number)
{
    uint8_t e = (*(((uint8_t*) &number)+3) & 0x7F) << 1;
    if (*(((uint8_t*) &number)+2) & 0x80) e++;
    return e;
}

*/
#endif
// END OF FILE