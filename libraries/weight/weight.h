#pragma once
//
//    FILE: weight.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Collection weight conversion functions
//     URL: https://github.com/RobTillaart/HX711
//
//  HISTORY:
//  0.1.0   2020-06-16  initial version
//  0.1.1   2021-01-09  add uarduino-ci + unit test


#include "Arduino.h"


#define WEIGHT_LIB_VERSION        (F("0.1.1"))


float lbs2kilo(float lbs)     { return lbs   * 0.45359237; };
float kilo2lbs(float kilos)   { return kilos * 2.20462262; };

float ounce2gram(float ounce) { return ounce * 28.3495231; };
float gram2ounce(float gram)  { return gram  * 0.03527396195; };

float gram2kilo(float gram)   { return gram  * 0.001; };
float kilo2gram( float kilo)  { return kilo  * 1000; };

float lbs2ounce(float lbs)    { return lbs   * 16; };
float ounce2lbs(float ounce)  { return ounce * 0.0625; };

float stone2lbs(float stone)  { return stone * 14; };
float lbs2stone(float lbs)    { return lbs   * 0.0714285714; };

float stone2kilo(float stone) { return stone * 6.35029318; };
float kilo2stone(float kilo)  { return kilo  * 0.157473044; };


// returns kilo
float US2metric(float stone, float lbs, float ounce)
{
  float kilo = stone * 6.35029318;
  kilo += lbs * 0.45359237;
  kilo += ounce * (0.0625 * 0.45359237);
  return kilo;
};


// returns lbs;
float metric2US(float kilo, float &stone, float &lbs, float &ounce)
{
  float val = kilo * 2.20462262;
  lbs = val;
  stone = int(lbs * 0.0714285714);
  lbs -= stone * 14;
  ounce = (lbs - int(lbs)) * 16;
  lbs = int(lbs);
  return val;
}

// -- END OF FILE --
