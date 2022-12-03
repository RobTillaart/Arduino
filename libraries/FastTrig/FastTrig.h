#pragma once 
//
//    FILE: FastTrig.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Arduino library for a faster approximation of sin() and cos()
//    DATE: 2011-08-18
//     URL: https://github.com/RobTillaart/FastTrig
//          https://forum.arduino.cc/index.php?topic=69723.0
//
// HISTORY: see changelog.md


#ifdef ESP_PLATFORM
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include "Arduino.h"
#endif


#define FAST_TRIG_LIB_VERSION             (F("0.2.0"))

#ifdef __cplusplus
extern "C"
{
#endif

extern uint16_t sinTable16[];
extern uint8_t sinTable8[];


///////////////////////////////////////////////////////
//
// GONIO LOOKUP
//
float isin(float f);

float icos(float x);

float itan(float f);

//  0 returns NAN but we have a icot(x) cotangent.
float icot(float f);


///////////////////////////////////////////////////////
//
//  INVERSE GONIO LOOKUP
//
float iasin(float f);

float iacos(float f);

//  PLACEHOLDER no good implementation (do not use).
float iatan(float f);


#ifdef __cplusplus
}
#endif


//  -- END OF FILE --
