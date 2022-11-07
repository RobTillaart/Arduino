#pragma once
//
//    FILE: FastTrig.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.11
// PURPOSE: Arduino library for a faster approximation of sin() and cos()
//    DATE: 2011-08-18
//     URL: https://github.com/RobTillaart/FastTrig
//          https://forum.arduino.cc/index.php?topic=69723.0
//
// HISTORY: see changelog.md


#include "Arduino.h"


#define FAST_TRIG_LIB_VERSION             (F("0.1.11"))


extern uint16_t isinTable16[];
extern uint8_t isinTable8[];

///////////////////////////////////////////////////////
//
// GONIO LOOKUP
//
float isin(float f);

float icos(float x);

float itan(float f);

// some problem at 0 but at least we have a icot(x) cotangent.
float icot(float f);

// missing function...
// float cot(float f);


///////////////////////////////////////////////////////
//
// INVERSE GONIO LOOKUP
//
float iasin(float f);

float iacos(float f);

// PLACEHOLDER no good implementation
float iatan(float f);


// -- END OF FILE --
