#pragma once
//
//    FILE: FastTrig.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: Arduino library for a faster approximation of sin() and cos()
//    DATE: 2011-08-18
//     URL: https://github.com/RobTillaart/FastTrig
//          https://forum.arduino.cc/index.php?topic=69723.0
//
//  HISTORY:
//  0.1.00  2011-08-18  initial version
//  0.1.01  2011-08-18  improved tables a bit + changed param to float
//  0.1.02  2011-08-20  added interpolation
//          eons passed
//  0.1.1   2020-08-30  refactor, create a library out of it.
//                      itan() approximation is bad.
//  0.1.2   2020-09-06  optimize 16 bit table with example sketch
//  0.1.3   2020-09-07  initial release.
//  0.1.4   2020-09-08  rewrite itan() + cleanup + examples
//  0.1.5   2020-09-11  fixed optimize, new table, added iasin() and iacos()
//  0.1.6   2020-12-23  arduino-CI + unit tests

#include "Arduino.h"

// 91 x 2 bytes ==> 182 bytes
// use 65535.0 as divider
uint16_t isinTable16[] = {
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


/* 0.1.4 table
uint16_t isinTable16[] = {
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
uint8_t isinTable8[] = { 
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
// GONIO LOOKUP
//
float isin(float f)
{
  boolean pos = true;  // positive
  if (f < 0)
  {
    f = -f;
    pos = !pos;
  }

  long x = f;
  uint8_t r = (f - x) * 256;

  if (x >= 360) x %= 360;

  int y = x; // 16 bit math is faster than 32 bit

  if (y >= 180)
  {
    y -= 180;
    pos = !pos;
  }

  if (y >= 90)
  {
    y = 180 - y;
    if (r != 0)
    {
      r = 255 - r;
      y--;
    }
  }

  // float v  improves ~4% on avg error  for ~60 bytes.
  uint16_t v = isinTable16[y];
  
  // interpolate if needed
  if (r > 0) 
  {
    v = v + ((isinTable16[y + 1] - v) / 8 * r) /32;   //  == * r / 256
  }
  float g = v * 0.0000152590219; // = /65535.0
  if (pos) return g;
  return -g;
}

float icos(float x)
{
  // prevent modulo math if x in 0..360
  return isin(x - 270.0);  // better than x + 90;
}

float itan(float f)
{
  // reference
  // return isin(f)/icos(f);
  
  // idea is to divide two (interpolated) values from the table 
  // so no divide by 65535
  
  // FOLDING
  bool neg = (f < 0);
  bool mir = false;
  if (neg) f = -f;

  long x = f;
  float rem = f - x;
  float v = x % 180 + rem;  // normalised value 0..179.9999
  if (v > 90)
  {
    v = 180 - v;
    neg = !neg;
    mir = true;
  }
  uint8_t d = v;
  if (d == 90) return 0;

  // COS FIRST
  uint8_t p = 90 - d;
  float co = isinTable16[p];
  if (rem != 0)
  {
    float delta = (isinTable16[p] - isinTable16[p - 1]);
    if (mir) co = isinTable16[p - 1] + rem * delta;
    else     co = isinTable16[p]     - rem * delta;
  }
  if (co == 0) return 0;

  float si = isinTable16[d];
  if (rem != 0) si += rem * (isinTable16[d + 1]  - isinTable16[d]);

  float ta = si/co;
  if (neg) return -ta;
  return ta;
}


///////////////////////////////////////////////////////
//
// INVERSE GONIO LOOKUP
//
float iasin(float f)
{
  bool neg = (f < 0);
  if (neg)
  {
    f = -f;
    neg = true;
  }
  uint16_t val = round(f * 65535);
  uint8_t lo = 0;
  uint8_t hi = 90;

  while (hi - lo > 1)
  {
    uint8_t mi = (lo + hi) / 2;
    if (isinTable16[mi] == val)
    {
      if (neg) return -mi;
      return mi;
    }
    if (isinTable16[mi] < val) lo = mi;
    else hi = mi;
  }  
  float delta = val - isinTable16[lo];
  uint16_t range = isinTable16[hi] - isinTable16[lo];
  delta /= range;
  if (neg) return -(lo + delta); 
  return (lo + delta);  
}

float iacos(float f)
{
  return 90 - iasin(f);
}

// PLACEHOLDER
float iatan(float f)
{
  return 0 * f;
}

// -- END OF FILE --
