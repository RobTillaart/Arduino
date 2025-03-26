#pragma once
//
//    FILE: decibel.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-12-19
// PURPOSE: fast decibel function
//     URL: https://github.com/RobTillaart/decibel


#ifdef ESP_PLATFORM
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include "Arduino.h"
#endif


#define DECIBEL_LIB_VERSION               (F("0.1.0"))


#ifdef __cplusplus
extern "C"
{
#endif


////////////////////////////////////////////////////////////
//
//  DECIBEL
//
//  AVR ~176 us
float decibel(float alpha)
{
  float a = alpha;
  if (a < 0) a = -a;
  return 10 * log10(a);
};

//  AVR ~204 us
float inverseDecibel(float alpha)
{
  float a = alpha * 0.1f ;
  return exp(a * log(10));
  //  return exp(alpha * 0.230258509299f);  //  approx equally fast
};


////////////////////////////////////////////////////////////
//
//  DECIBEL FAST - less exact
//
//  https://openaudio.blogspot.com/2017/02/faster-log10-and-pow.html
//  and several other places describe a fast approximation for log2().
//  y = C[0]*f*f*f + C[1]*f*f + C[2]*f + C[3] + exponent;
//  As log10(x) = log2(x) * 0.3010299956639812f  //  0.30... == log(2)/log(10).
//  the decibel math can be done a bit faster.
//  The price is accuracy.
//
//  AVR ~80 us
float decibelFast(float alpha)
{
  float a = alpha;
  if (a < 0) a = -a;
  int exponent;
  float value = frexpf(a, &exponent);
  float y = 1.23149591368684f;
  y *= value;
  y += -4.11852516267426f;
  y *= value;
  y += 6.02197014179219f;
  y *= value;
  y += -3.13396450166353f;
  y += exponent;
  return y * 3.010299956639812f;
};


#ifdef __cplusplus
}
#endif



//  -- END OF FILE --

