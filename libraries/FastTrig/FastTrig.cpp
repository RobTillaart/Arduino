//
//    FILE: FastTrig.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library for a faster approximation of sin() and cos()
//    DATE: 2011-08-18
//     URL: https://github.com/RobTillaart/FastTrig
//          https://forum.arduino.cc/index.php?topic=69723.0


#include "FastTrig.h"


//  91 x 2 bytes ==> 182 bytes
//  use 65535.0 as divider
uint16_t sinTable16[] = {
  0,
1145, 2289, 3435, 4572, 5716, 6853, 7989, 9125, 10255, 11385,
12508, 13631, 14745, 15859, 16963, 18067, 19165, 20253, 21342, 22417,
23489, 24553, 25610, 26659, 27703, 28731, 29755, 30773, 31777, 32772,
33756, 34734, 35697, 36649, 37594, 38523, 39445, 40350, 41247, 42131,
42998, 43856, 44701, 45528, 46344, 47147, 47931, 48708, 49461, 50205,
50933, 51646, 52342, 53022, 53686, 54334, 54969, 55579, 56180, 56760,
57322, 57866, 58394, 58908, 59399, 59871, 60327, 60768, 61184, 61584,
61969, 62330, 62677, 63000, 63304, 63593, 63858, 64108, 64334, 64545,
64731, 64903, 65049, 65177, 65289, 65377, 65449, 65501, 65527, 65535,
65535
};


/*  0.1.4 table
uint16_t sinTable16[] = {
  0,
  1145, 2289, 3435, 4571, 5715, 6852, 7988, 9125, 10254, 11385,
  12508, 13630, 14745, 15859, 16963, 18067, 19165, 20253, 21342, 22416,
  23488, 24553, 25610, 26659, 27699, 28730, 29754, 30773, 31777, 32771,
  33755, 34734, 35697, 36649, 37594, 38523, 39445, 40350, 41247, 42127,
  42998, 43856, 44697, 45527, 46344, 47146, 47931, 48708, 49461, 50205,
  50933, 51645, 52341, 53022, 53686, 54333, 54969, 55578, 56180, 56759,
  57322, 57866, 58394, 58908, 59399, 59871, 60327, 60767, 61184, 61584,
  61969, 62330, 62677, 63000, 63304, 63592, 63857, 64108, 64333, 64544,
  64731, 64902, 65049, 65177, 65289, 65376, 65449, 65501, 65527, 65535,
  65535
};
*/


// use 255.0 as divider
uint8_t sinTable8[] = {
  0, 4, 9, 13, 18, 22, 27, 31, 35, 40, 44,
  49, 53, 57, 62, 66, 70, 75, 79, 83, 87,
  91, 96, 100, 104, 108, 112, 116, 120, 124, 128,
  131, 135, 139, 143, 146, 150, 153, 157, 160, 164,
  167, 171, 174, 177, 180, 183, 186, 190, 192, 195,
  198, 201, 204, 206, 209, 211, 214, 216, 219, 221,
  223, 225, 227, 229, 231, 233, 235, 236, 238, 240,
  241, 243, 244, 245, 246, 247, 248, 249, 250, 251,
  252, 253, 253, 254, 254, 254, 255, 255, 255, 255,
  255
};


///////////////////////////////////////////////////////
//
// GONIO INT EXPERIMENTAL
// works with only whole degrees.
//
int isin256(uint32_t v)
{
  bool negative = false;

  long whole = v;

  if (whole >= 360) whole %= 360;

  int y = whole;  //  16 bit math is faster than 32 bit

  if (y >= 180)
  {
    y -= 180;
    negative = true;
  }

  if (y >= 90)
  {
    y = 180 - y;
  }

  int g = sinTable16[y] >> 8;
  if (negative) return -g;
  return g;
}


int icos256(uint32_t v)
{
  return isin256(v + 90);
}


void isincos256(uint32_t v, int *si, int *co)
{
  bool sneg = false;
  bool cneg = false;

  long whole = v;

  if (whole >= 360)
  {
    whole %= 360;
  }

  int y = whole;  //  16 bit math is faster than 32 bit

  if (y >= 180)
  {
    y -= 180;
    sneg = !sneg;
    cneg = !cneg;
  }

  if (y >= 90)
  {
    y = 180 - y;
    cneg = !cneg;
  }

  *si = sinTable16[y] >> 8;
  *co = sinTable16[90-y] >> 8;
  if (sneg) *si = - *si;
  if (cneg) *co = - *co;
}


///////////////////////////////////////////////////////
//
//  GONIO LOOKUP
//
float isin(float f)
{
  bool negative = (f < 0);
  if (negative)
  {
    f = -f;
    negative = true;
  }

  long whole = f;
  uint8_t remain = (f - whole) * 256;

  if (whole >= 360)
  {
    whole %= 360;
    //  possible faster for 360-720
    //  if (whole >= 720) whole %= 360;
    //  else whole -= 360;
  }

  int y = whole;  //  16 bit math is faster than 32 bit

  if (y >= 180)
  {
    y -= 180;
    negative = !negative;
  }

  if (y >= 90)
  {
    y = 180 - y;
    if (remain != 0)
    {
      remain = 256 - remain;
      y--;
    }
  }

  //  float value  improves ~4% on avg error  for ~60 bytes.
  uint16_t value = sinTable16[y];

  //  interpolate if needed
  if (remain > 0)
  {
    value = value + ((sinTable16[y + 1] - value) / 8 * remain) / 32;   //  == * remain / 256
  }
  float g = value * 0.0000152590219;  //  = / 65535.0
  if (negative) return -g;
  return g;
}


float icos(float x)
{
  //  prevent modulo math if x in 0..360
  return isin(x - 270.0);  //  better than x + 90;
}


void isincos(float f, float *si, float *co)
{
  bool sneg = (f < 0);
  bool cneg = false;
  if (sneg)
  {
    f = -f;
  }

  long whole = f;
  uint8_t remain = (f - whole) * 256;

  if (whole >= 360)
  {
    whole %= 360;
    //  possible faster for 360-720
    //  if (whole >= 720) whole %= 360;
    //  else whole -= 360;
  }

  int y = whole;  //  16 bit math is faster than 32 bit

  if (y >= 180)
  {
    y -= 180;
    sneg = !sneg;
    cneg = !cneg;
  }

  if (y >= 90)
  {
    y = 180 - y;
    if (remain != 0)
    {
      remain =   - remain;
      y--;
    }
    cneg = !cneg;
  }

  //  float value  improves ~4% on avg error  for ~60 bytes.
  //  SIN
  uint16_t value = sinTable16[y];
  //  interpolate if needed
  if (remain > 0)
  {
    value = value + ((sinTable16[y + 1] - value) / 8 * remain) / 32;  //  == * remain / 256
  }
  *si = value * 0.0000152590219;  //  = / 65535.0
  if (sneg) *si = - *si;

  //  COS
  value = sinTable16[90-y];
  if (remain > 0)
  {
    value = sinTable16[89-y];
    remain = 256 - remain;
    value = value + ((sinTable16[90-y] - value) / 8 * remain) / 32;  //  == * remain / 256
  }
  *co = value * 0.0000152590219;  //  = / 65535.0
  if (cneg) *co = - *co;
}


///////////////////////////////////////////////
//
//  TAN
//
//  tan() should be done with isincos()
//  as icos() is less accurate => tan() less accurate.
/*
float itan(float f)
{
  float x, y;
  isincos(f,x,y);
  if (y != 0) return x/y;
  return NAN;
}
*/


float itan(float f)
{
  //  reference
  //  return isin(f)/icos(f);

  //  idea is to divide two (interpolated) values from the table
  //  so no divide by 65535

  //  FOLDING
  bool mirror = false;
  bool negative = (f < 0);
  if (negative) f = -f;

  long whole = f;
  float remain = f - whole;
  if (whole >= 180) whole %= 180;
  float value = remain + whole;  //  normalised value 0..179.9999
  if (value > 90)
  {
    value = 180 - value;
    negative = !negative;
    mirror = true;
  }
  uint8_t d = value;
  if (d == 90) return NAN;

  //  COS FIRST
  uint8_t p = 90 - d;
  float co = sinTable16[p];
  if (remain != 0)
  {
    float delta    = (sinTable16[p] - sinTable16[p - 1]);
    if (mirror) co = sinTable16[p - 1] + remain * delta;
    else        co = sinTable16[p]     - remain * delta;
  }
  else if (co == 0) return 0;

  float si = sinTable16[d];
  if (remain != 0) si += remain * (sinTable16[d + 1]  - sinTable16[d]);

  float ta = si/co;
  if (negative) return -ta;
  return ta;
}


//  some problem at 0 but at least we have a icot(x) cotangent.
float icot(float f)
{
  float ta = itan(f);
  if (ta == 0) return NAN;
  return 1.0 / ta;
}


///////////////////////////////////////////////////////
//
//  INVERSE GONIO LOOKUP
//
float iasin(float f)
{
  bool negative = (f < 0);
  if (negative)
  {
    f = -f;
    negative = true;
  }
  uint16_t value = round(f * 65535);
  uint8_t lo = 0;
  uint8_t hi = 90;

  while (hi - lo > 1)
  {
    uint8_t mi = (lo + hi) / 2;
    if (sinTable16[mi] == value)
    {
      if (negative) return -mi;
      return mi;
    }
    if (sinTable16[mi] < value) lo = mi;
    else hi = mi;
  }
  float delta = value - sinTable16[lo];
  uint16_t range = sinTable16[hi] - sinTable16[lo];
  delta /= range;
  if (negative) return -(lo + delta);
  return (lo + delta);
}


float iacos(float f)
{
  return 90 - iasin(f);
}


//  PLACEHOLDER
float iatan(float f)
{
  return 0 * f;
}


float atanFast(float x)
{
  //  remove two test will limit the input range but makes it even faster.
  if ( x > 1)  return ( M_PI / 2) - atanHelper(1.0 / x);
  if ( x < -1) return (-M_PI / 2) - atanHelper(1.0 / x);
  return atanHelper(x);
}


inline float atanHelper(float x)
{
  float x2 = x * x;
  return (((0.079331 * x2) - 0.288679) * x2 + 0.995354) * x;

  //  an even more accurate alternative, less fast
  //  return ((((-0.0389929 * x2) + 0.1462766) * x2 - 0.3211819) * x2 + 0.9992150) * x;
}


float atan2Fast(float y, float x)
{
  //  catch singularity.
  if ((x == 0) && (y == 0)) return NAN;

  if (x >= 0)
  {
    if (y >= 0)
    {
      if (fabs(y) >= fabs(x)) return M_PI / 2 - atanFast(x / y);
      return atanFast(y / x);
    }
    if (fabs(y) >= fabs(x)) return -M_PI / 2 - atanFast(x / y);
    return atanFast(y / x);
  }
  else
  {
    if (y >= 0)
    {
      if (fabs(y) >= fabs(x)) return M_PI / 2 - atanFast(x / y);
      return M_PI + atanFast(y / x);
    }
    if (fabs(y) >= fabs(x)) return -M_PI / 2 - atanFast(x / y);
    return -M_PI + atanFast(y / x);
  }
}


///////////////////////////////////////////////////////
//
//  HYPOT
//  related but not strict gonio.
//
//  hypotFast()  formula for faster hypot() at the price of accuracy
//  experimental!
float hypotFast(float x, float y)
{
  float a = fabs(x);
  float b = fabs(y);
  if (a > b)
  {
    a = fabs(y);
    b = fabs(x);
  }
  float z = 0.917981 * (b + a / 2);
  if (z > b) return z;
  return b;
}


//  -- END OF FILE --

