#pragma once
//
//    FILE: FastTrig.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library for a faster approximation of sin() and cos()
//    DATE: 2011-08-18
//     URL: https://github.com/RobTillaart/FastTrig
//          https://forum.arduino.cc/index.php?topic=69723.0


#ifdef ESP_PLATFORM
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include "Arduino.h"
#endif


#define FAST_TRIG_LIB_VERSION             (F("0.3.3"))

#ifdef __cplusplus
extern "C"
{
#endif

extern uint16_t sinTable16[];
extern uint8_t sinTable8[];


///////////////////////////////////////////////////////
//
//  GONIO INT EXPERIMENTAL
//
int isin256(uint32_t v);
int icos256(uint32_t v);
//  calculate both in one call.
void isincos256(uint32_t v, int *si, int *co);


///////////////////////////////////////////////////////
//
//  GONIO LOOKUP
//
float isin(float f);
float icos(float x);
//  calculate both in one call.
void isincos(float v, float *si, float *co);
float itan(float f);
//  0 returns NAN but we have a icot(x) cotangent.
float icot(float f);


///////////////////////////////////////////////////////
//
//  INVERSE GONIO LOOKUP
//
float iasin(float f);
float iacos(float f);

//  PLACEHOLDER (might be obsolete due to atanFast() formula.
float iatan(float f);
//  fast atan() formula, in fact a modified Taylor expansion
//  input = -1 .. 1
float atanFast(float f);

inline float atanHelper(float x);

//  atan2Fast() folds and mirrors => calls atanFast() + offset.
float atan2Fast(float y, float x);


///////////////////////////////////////////////////////
//
//  HYPOT
//  related but not strict gonio.
//
//  hypotFast()  formula for faster hypot() at the price of accuracy
//  experimental!
float hypotFast(float x, float y);


#ifdef __cplusplus
}
#endif


//  -- END OF FILE --
