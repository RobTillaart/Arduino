//
//    FILE: A1301.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.


#include "A1301.h"


HALL::HALL(uint8_t pin)
{
  _pin       = pin;
  _midPoint  = 512;
  _lastGauss = 0;
  _mVGauss   = 2.5;
  _mVStep    = 5000.0 / 1023;  //  default 10 bit 5V ADC
}


void HALL::begin(float voltage, uint16_t steps)
{
  _mVStep = voltage / steps;
}


void HALL::setMidPoint(float midPoint)
{
  _midPoint = midPoint;
}


float HALL::getMidPoint()
{
  return _midPoint;
}


void HALL::setSensitivity(float sensitivity)
{
  _mVGauss = sensitivity;
}


float HALL::getSensitivity()
{
  return _mVGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  READ
//
float HALL::raw(uint8_t times)
{
  float sum = 0;
  if (times == 0) times = 1;
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_pin);
  }
  if (times > 1) sum /= times;
  return sum;
}


float HALL::read(uint8_t times)
{
  float milliVolts = (raw(times) - _midPoint) * _mVStep;
  _prevGauss = _lastGauss;
  _lastGauss = milliVolts / _mVGauss;
  return _lastGauss;
}


float HALL::readExt(float raw)
{
  float milliVolts = (raw - _midPoint) * _mVStep;
  _prevGauss = _lastGauss;
  _lastGauss = milliVolts / _mVGauss;
  return _lastGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  ANALYSE
//
boolean HALL::isNorth()
{
  return (_lastGauss > 0);
}


boolean HALL::isSouth()
{
  return (_lastGauss < 0);
}


float HALL::lastGauss()
{
  return _lastGauss;
}


float HALL::prevGauss()
{
  return _prevGauss;
}


//  CONVERTORs
float HALL::Tesla(float Gauss)
{
  return Gauss * 0.0001;
}


float HALL::mTesla(float Gauss)
{
  return Gauss * 0.1;
}


float HALL::uTesla(float Gauss)
{
  return Gauss * 100;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED
//
A1301::A1301(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 2.5;
}


A1302::A1302(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 1.3;
}


//  -- END OF FILE --

