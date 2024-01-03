//
//    FILE: fast_math.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino library for fast math algorithms
//    DATE: 27 October 2013
//     URL: https://github.com/RobTillaart/fast_math


#include "fast_math.h"


///////////////////////////////////////////////////////////
//
//  DIV MOD
//
void divmod10(uint32_t in, uint32_t *div, uint8_t *mod)
{
    uint32_t x = (in|1) - (in >> 2);   //  div = in/10 <~~> div = (0.8*in) / 8
    uint32_t q = (x >> 4) + x;         //  0.796875 *in
    x = q;
    q = (q >> 8) + x;                  //  0.799987793 * in
    q = (q >> 8) + x;                  //  0.803112745 * in
    q = (q >> 8) + x;                  //  0.8... * in
    q = (q >> 8) + x;                  //  0.8... * in

    x = (q >> 2);
    *div = (x >> 1);
    *mod = in - ((q & ~0x7) + (*div << 1));
}


void divmod3(uint32_t in, uint32_t *div, uint8_t *mod)
{
    uint32_t q = (in >> 1) + (in >> 3);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 1;
    uint32_t r = in - q * 3;
    q = q + (r * 86 >> 8);
    *div = q;
    *mod = in - q * 3;
}


void divmod5(uint32_t in, uint32_t *div, uint8_t *mod)
{
    uint32_t q = (in >> 1) + (in >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 2;
    uint32_t r = in - q * 5;  //  remainder  approx
    q = q + (r * 56 >> 8);
    *div = q;
    *mod = in - q * 5;
}


void divmod12(uint32_t in, uint32_t *div, uint8_t *mod)
{
  uint32_t d;
  uint8_t  m;
  divmod3(in, &d, &m);
  *div = d >> 2;
  *mod = m + (d & 0x03) * 3;
}


void divmod24(uint32_t in, uint32_t *div, uint8_t *mod)
{
  uint32_t d;
  uint8_t  m;
  divmod3(in, &d, &m);
  *div = d >> 3;
  *mod = m + (d & 0x07) * 3;
}


void divmod60(uint32_t in, uint32_t *div, uint8_t *mod)
{
  uint32_t q = (in >> 1) + (in >> 5);
  q = (q + (q >> 8) + (q >> 16) + (q >> 24) ) >> 5;
  uint8_t r = in - q*60;
  if (r > 59) { q++; r -= 60; };  // correction.
  *div = q;
  *mod = r;
}



///////////////////////////////////////////////////////////
//
//  BCD
//
uint8_t dec2bcdRef(uint8_t value)
{
  //  two common versions.
  // return (value / 10 * 16 +  value % 10);
  return value + 6 * (value / 10);
}


uint8_t dec2bcd(uint8_t value)
{
  uint8_t b = (value * 103) >> 10;
  return (b * 16 + value - (b * 10)); 
  // return value + 6 * b;   //  compiles equally fast.
}


uint8_t dec2bcdRTC(uint8_t value)
{
  //  this trick works faster for range value = 0..60 (think RTC).
  uint16_t a = value;
  uint8_t  b = (a * 26) >> 8;   //  magic * 26 / 256 ~~ / 10
  uint8_t  c = value + b * 6;
  //  if ((c & 0x0F) == 0x0F) c -= 6;  // extends range to 0..99
  return c;
}


uint8_t bcd2decRef(uint8_t value)
{
  return value/16 * 10 + value % 10;
}


uint8_t bcd2dec(uint8_t value)
{
  return value - 6 * (value >> 4);
}


///////////////////////////////////////////////////////////
//
//  POLYNOME
//
float polynome(float x, float ar[], uint8_t degree)
{
  float value = ar[0];
  float p = x;
  for (uint8_t i = 1; i <= degree; i++)
  {
    if (ar[i] != 0.0)
    {
      if (ar[i] == 1.0) value += p;
      else value += ar[i] * p;
    }
    p *= x;
  }
  return value;
}


///////////////////////////////////////////////////////////
//
//  PING
//
uint16_t ping2cm(uint16_t in)
{
  //  divide by 29.41176 == * 0.034
  //  uint16_t q = (in >> 5) + (in >> 9) + (in >> 11) + (in >> 12) + (in >> 14);
  uint16_t d = in >> 5;
  uint16_t q = d;
  d >>= 4;  //  in >> 9
  q += d;
  d >>= 2;  //  in >> 11;
  q += d;
  d >>= 1;  //  in >> 12
  q += d;
  d >>= 2;  //  in >> 14
  q += d + 2;
  return q;
}


uint16_t ping2mm(uint16_t in)
{
  //  divide by 2.941176 == * 0.34;
  //  uint16_t q = (in >> 2) + (in >> 4) + (in >> 6) + (in >> 7) + (in >> 8) + (in >> 13);
  uint16_t d = in >> 2;
  uint16_t q = d;
  d >>= 2;  //  in >> 4
  q += d;
  d >>= 2;  //  in >> 6;
  q += d;
  d >>= 1;  //  in >> 7
  q += d;
  d >>= 1;  //  in >> 8
  q += d;
  d >>= 5;  //  in >> 13
  q += d + 3;
  return q;
}


uint16_t ping2inch(uint16_t in)
{
  //  divide by 74.70588235 == * 0.0133858
  //  uint16_t q = (in >> 7) + (in >> 8) + (in >> 10) + (in >> 11) + (in >> 13) + (in >> 14) ;
  uint16_t d = in >> 7;
  uint16_t q = d;
  d >>= 1;  //  in >> 8
  q += d;
  d >>= 2;  //  in >> 10
  q += d;
  d >>= 1;  //  in >> 11
  q += d;
  d >>= 2;  //  in >> 13
  q += d;
  d >>= 1;  //  in >> 14
  q += d + 2;  //  correction.
  return q;
}


uint16_t ping2quarter(uint16_t in)
{
  //  divide by 18.6764705875 == * 0.05354330709
  //  uint16_t q = (in >> 5) + (in >> 6) + (in >> 8) + (in >> 9) + (in >> 11) + (in >> 12) + (in >> 14) ;
  uint16_t d = in >> 5;
  uint16_t q = d;
  d >>= 1;  //  in >> 6
  q += d;
  d >>= 2;  //  in >> 8
  q += d;
  d >>= 1;  //  in >> 9
  q += d;
  d >>= 2;  //  in >> 11
  q += d;
  d >>= 1;  //  in >> 12
  q += d;
  d >>= 2;  //  in >> 14
  q += d + 3;  //  correction.
  return q;
}


uint16_t ping2sixteenths(uint16_t in)
{
  //  divide by 4.669117646875 == * 0.214173228
  //  uint16_t q = (in >> 3) + (in >> 4) + (in >> 6) + (in >> 7) + (in >> 9) + (in >> 10) + (in >> 12) + (in >> 14) ;
  uint16_t d = in >> 3;
  uint16_t q = d;
  d >>= 1;  //  in >> 4
  q += d;
  d >>= 2;  //  in >> 6
  q += d;
  d >>= 1;  //  in >> 7
  q += d;
  d >>= 2;  //  in >> 9
  q += d;
  d >>= 1;  //  in >> 10
  q += d;
  d >>= 2;  //  in >> 12
  q += d;
  d >>= 2;  //  in >> 14
  q += d + 3;  //  correction.
  return q;
}


/////////////////////////////////////////////////////////////////////////////////////


uint32_t ping2cm32(uint32_t in)
{
  //  divide by 29.41176 == * 0.034
  //  uint32_t q = (in >> 5) + (in >> 9) + (in >> 11) + (in >> 12) + (in >> 14) 
  //             + (in >> 19) + (in >> 20) + (In >> 21) + (in >> 24) + (26, 28 29...;
  uint32_t d = in >> 5;
  uint32_t q = d;
  d >>= 4;  //  in >> 9
  q += d;
  d >>= 2;  //  in >> 11;
  q += d;
  d >>= 1;  //  in >> 12
  q += d;
  d >>= 2;  //  in >> 14
  q += d;
  d >>= 5;  //  in >> 19
  // q += d;
  // d >>= 1;  //  in >> 20
  // q += d;
  // d >>= 1;  //  in >> 21
  // q += d;
  // d >>= 3;  //  in >> 24
  // q += d;
  // d >>= 2;  //  in >> 26;
  // q += d;
  // d >>= 2;  //  in >> 28
  // q += d;
  // d >>= 1;  //  in >> 29
  q += d + 3;   //  rounding correction
  return q;
}


uint32_t ping2mm32(uint32_t in)
{
  // divide by 2.941176 == * 0.34;
  // uint32_t q = (in >> 2) + (in >> 4) + (in >> 6) + (in >> 7) + (in >> 8) + (in >> 13);
  //               15, 19, 20, 21, 22, 24, 26, 27, 28
  uint32_t d = in >> 2;
  uint32_t q = d;
  d >>= 2;  //  in >> 4
  q += d;
  d >>= 2;  //  in >> 6
  q += d;
  d >>= 1;  //  in >> 7
  q += d;
  d >>= 1;  //  in >> 8
  q += d;
  d >>= 5;  //  in >> 13
  q += d;
  d >>= 2;  //  in >> 15
  q += d;
  d >>= 4;  //  in >> 19
  // q += d;
  // d >>= 1;  //  in >> 20
  // q += d;
  // d >>= 1;  //  in >> 21
  // q += d;
  // d >>= 1;  //  in >> 22
  // q += d;
  // d >>= 2;  //  in >> 24
  // q += d;
  // d >>= 2;  //  in >> 26
  // q += d;
  // d >>= 1;  //  in >> 27
  // q += d;
  // d >>= 1;  //  in >> 28
  q += d + 3;   //  rounding correction.
  return q;
}


/////////////////////////////////////////////////////////////////////////////////////


//  temperature in Celsius
float ping2cm_tempC(uint16_t duration, int Celsius )
{
  //
  //  return duration * 331.45 * sqrt(1 + temp / 273.0) / 10000;
  //  return duration * 331.45 * sqrt(1 + temp * (1.0 / 273.0)) * 0.0001;
  //  return duration * 331.45 * (1 + temp * (1.0 / 546.0)) * 0.0001;  //  little less accurate sqrt
  return duration * (0.033145 + Celsius * (0.033145 / 546.0));     //  minimized.
}


float ping2inch_tempC(uint16_t duration, int Celsius )
{
  //  formula ping2cm_tempC converted
  return duration * (0.013049 + Celsius * (0.013049 / 546.0));
}


float ping2inch_tempF(uint16_t duration, int Fahrenheit )
{
  //  formula ping2inch_tempC converted
  //  return duration * 331.45 * sqrt(1 + temp * (1.0 / 273.0)) * 0.0001;
  //  inches
  //  return duration * 130.49 * (1 + temp * (1.0 / 546.0)) * 0.0001;  //  little less accurate sqrt
  //  Fahrenheit
  //  return duration * (0.013049 + (Fahrenheit - 32) * (5.0/9.0) * (0.013049 / 546.0));
  return duration * (0.013049 + (Fahrenheit - 32) * ((5.0/9.0) * (0.013049 / 546.0)));
}


///////////////////////////////////////////////////////////
//
//  TODO ...
//


//  -- END OF FILE --

