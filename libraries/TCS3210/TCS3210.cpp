//
//    FILE: TCS3210.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for TCS3210 colour light to frequency convertor.
//    DATE: 2025-01-12
//     URL: https://github.com/RobTillaart/TCS3210


#include "TCS3210.h"


TCS3210::TCS3210(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data)
{
  _s0 = S0;
  _s1 = S1;
  _s2 = S2;
  _s3 = S3;
  _oe = OE;
  _data = data;
  _type = 10;
}

bool TCS3210::begin()
{
  pinMode(_oe, INPUT);
  enable();
  pinMode(_data, INPUT);
  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  set100Percent();
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  selectNone();
  return true;
}

uint8_t TCS3210::getType()
{
  return _type;
}


void TCS3210::enable()  { digitalWrite(_oe, LOW); };
void TCS3210::disable() { digitalWrite(_oe, HIGH); };


//  SELECT COLOUR FILTER
void TCS3210::selectRed()     { _setFilter(0); };
void TCS3210::selectGreen()   { _setFilter(3); };
void TCS3210::selectBlue()    { _setFilter(1); };
void TCS3210::selectNone()    { _setFilter(2); };


//  SELECT OUTPUT
void TCS3210::powerDown()     {  _setPercentage(0); };
void TCS3210::set2Percent()   {  _setPercentage(1); };
void TCS3210::set20Percent()  {  _setPercentage(2); };
void TCS3210::set100Percent() {  _setPercentage(3); };


//  READ
uint32_t TCS3210::getDuration(uint16_t ms)
{
  //  check OE pin too?
  if (_factor == 0) return 0;
  return pulseIn(_data, LOW, (ms * 1000));
}

float TCS3210::getFrequency(uint16_t ms)
{
  uint32_t duration = pulseIn(_data, LOW, (ms * 1000));
  if (duration == 0) return 0;
  float frequency = (_factor * 0.01 * 1e6) / duration;
  return frequency;
}


////////////////////////////////////////////////////
//
//  PROTECTED
//
void TCS3210::_setFilter(uint8_t n)
{
  digitalWrite(_s2, n & 1 ? HIGH : LOW);
  digitalWrite(_s3, n & 2 ? HIGH : LOW);
}

void TCS3210::_setPercentage(uint8_t n)
{
  digitalWrite(_s0, n & 1 ? HIGH : LOW);
  digitalWrite(_s1, n & 2 ? HIGH : LOW);
  //  update correction factor
  _factor = 0;
  if (n == 1) _factor = 2;
  else if (n == 2) _factor = 20;
  else if (n == 3) _factor = 100;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS TCS3200
//
TCS3200::TCS3200(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t OE, uint8_t data)
        :TCS3210(S0, S1, S2, S3, OE, data)
{
  _type = 0;
}


//  -- END OF FILE --

