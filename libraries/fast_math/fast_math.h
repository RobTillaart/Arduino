#pragma once
//
//    FILE: fast_math.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
// PURPOSE: Arduino library for fast math algorithms
//    DATE: 27 October 2013
//     URL: https://github.com/RobTillaart/fast_math


#ifdef ESP_PLATFORM
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include "Arduino.h"
#endif

#define FASTMATH_LIB_VERSION          (F("0.2.3"))


#ifdef __cplusplus
extern "C"
{
#endif


//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: divmod10
//  PURPOSE: fast routine that provides both / 10 and % 10 for integer math.
//      URL: https://forum.arduino.cc/t/divmod10-a-fast-replacement-for-10-and-10-unsigned/163586
//  AUTHORS: see URL
//     NOTE: assembler version for AVR exists (by Stimmer) - see URL
//
void divmod10(uint32_t in, uint32_t *div, uint8_t *mod);
void divmod3(uint32_t in, uint32_t *div, uint8_t *mod);
void divmod5(uint32_t in, uint32_t *div, uint8_t *mod);

//  for clocks
void divmod12(uint32_t in, uint32_t *div, uint8_t *mod);
void divmod24(uint32_t in, uint32_t *div, uint8_t *mod);
void divmod60(uint32_t in, uint32_t *div, uint8_t *mod);



//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: dec2bcd and bcd2dec
//  PURPOSE: conversion
//
uint8_t dec2bcdRef(uint8_t value);   //  reference implementation.
uint8_t dec2bcd(uint8_t value);
uint8_t dec2bcdRTC(uint8_t value);
uint8_t bcd2decRef(uint8_t value);
uint8_t bcd2dec(uint8_t value);


//////////////////////////////////////////////////////////////////////////
//
//  ROUTINE: polynome
//  PURPOSE: routine to evaluate a polynome and be able to change weights runtime.
//
//  assumes degree >= 1, and ar[0] exists, and could be 0.
//
//  e.g y = 3x^2 + 5x + 7 ==> ar[] = { 7, 5, 3 };  degree = 2;
//                            index is exponent of x
//                            7x^0 + 5x^1 + 3x^2
//
float polynome(float x, float ar[], uint8_t degree);


//////////////////////////////////////////////////////////////////////////
//
//  16 BIT PING MATH - for distances up to ~10 meter
//
//////////////////////////////////////////////////////////
//
//  ROUTINE: ping2cm
//  PURPOSE: fast routines to calculate the distance in cm / mm for a ping sensor
//
uint16_t ping2cm(uint16_t in);
uint16_t ping2mm(uint16_t in);  //  smaller units are more accurate.

uint16_t ping2inch(uint16_t in);
uint16_t ping2quarter(uint16_t in);
uint16_t ping2sixteenths(uint16_t in);


//////////////////////////////////////////////////////////
//
//  32 BIT PING MATH - for distances > 10 meter (gaim ~10%)
//
uint32_t ping2cm32(uint32_t in);
uint32_t ping2mm32(uint32_t in);


//  temperature compensated speed of sound distance
float ping2cm_tempC(uint16_t duration, int Celsius);
float ping2inch_tempC(uint16_t duration, int Celsius);
float ping2inch_tempF(uint16_t duration, int Fahrenheit);


#ifdef __cplusplus
}
#endif


//  -- END OF FILE --

