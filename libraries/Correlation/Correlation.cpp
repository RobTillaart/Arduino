//
//    FILE: Correlation.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino Library to determine correlation between X and Y dataset
//     URL: https://github.com/RobTillaart/Correlation


#include "Correlation.h"


Correlation::Correlation(uint8_t size)
{
  _size = 20;
  if (size >  0) _size = size;
  _x = (float *) malloc(_size * sizeof(float));
  _y = (float *) malloc(_size * sizeof(float));
  clear();
}


Correlation::~Correlation()
{
  if (_x) free(_x);
  if (_y) free(_y);
}


void Correlation::clear()
{
  _count           = 0;
  _index           = 0;
  _needRecalculate = true;
  _runningMode     = false;
  _avgX            = 0;
  _avgY            = 0;
  _a               = 0;
  _b               = 0;
  _div_b           = -1;  //  as 1/_b is undefined
  _r               = 0;
  _sumErrorSquare  = 0;
  _sumXiYi         = 0;
  _sumXi2          = 0;
  _sumYi2          = 0;
  _doR2            = true;
  _doE2            = true;
}


bool Correlation::add(float x, float y)
{
  if ( (_count < _size) || _runningMode)
  {
    _x[_index] = x;
    _y[_index] = y;
    _index++;
    if (_index >= _size) _index = 0;
    if (_count < _size) _count++;
    _needRecalculate = true;
    return true;
  }
  return false;
}


bool Correlation::calculate(bool forced)
{
  if (_count == 0) return false;
  if (! (_needRecalculate || forced)) return true;

  //  CALC AVERAGE X, AVERAGE Y
  float avgx = 0;
  float avgy = 0;
  float div_count = 1.0 / _count;  //  speed up averaging
  for (uint8_t i = 0; i < _count; i++)
  {
    avgx += _x[i];
    avgy += _y[i];
  }
  avgx *= div_count;
  avgy *= div_count;

  _avgX = avgx;
  _avgY = avgy;

  //  CALC A and B  ==>  formula  Y = A + B * X
  float sumXiYi = 0;
  float sumXi2  = 0;
  float sumYi2  = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    float xi = _x[i] - avgx;
    float yi = _y[i] - avgy;
    sumXiYi += (xi * yi);
    sumXi2  += (xi * xi);
    sumYi2  += (yi * yi);
  }
  float b = sumXiYi / sumXi2;
  float a = avgy - b * avgx;

  _a       = a;
  _b       = b;
  _div_b   = 1.0 / b;
  _sumXiYi = sumXiYi;
  _sumXi2  = sumXi2;
  _sumYi2  = sumYi2;

  if (_doR2 == true)
  {
    //  R is calculated instead of rSquared so we do not loose the sign.
    //  Rsquared  from R is much faster than R from Rsquared.
    _r = sumXiYi / sqrt(sumXi2 * sumYi2);
  }

  if (_doE2 == true)
  {
    float sumErrorSquare = 0;
    for (uint8_t i = 0; i < _count; i++)
    {
      float EY =  a + b * _x[i];
      float ei = _y[i] - EY;
      sumErrorSquare += (ei * ei);
    }
    _sumErrorSquare = sumErrorSquare;
  }
  _needRecalculate = false;
  return true;
}


float Correlation::getEstimateY(float x)
{
  if (_count == 0) return NAN;
  if (_needRecalculate) calculate();
  return _a + _b * x;
}


float Correlation::getEstimateX(float y)
{
  if (_count == 0) return NAN;
  if (_needRecalculate) calculate();
  return (y - _a) * _div_b;
}


//////////////////////////////////////////////////////
//
//  STATISTICAL
//
float Correlation::getMaxX()
{
  if (_count == 0) return NAN;
  float rv = _x[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_x[i] > rv) rv = _x[i];
  }
  return rv;
}


float Correlation::getMinX()
{
  if (_count == 0) return NAN;
  float rv = _x[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_x[i] < rv) rv = _x[i];
  }
  return rv;
}


float Correlation::getMaxY()
{
  if (_count == 0) return NAN;
  float rv = _y[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_y[i] > rv) rv = _y[i];
  }
  return rv;
}


float Correlation::getMinY()
{
  if (_count == 0) return NAN;
  float rv = _y[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_y[i] < rv) rv = _y[i];
  }
  return rv;
}


//////////////////////////////////////////////////////
//
//  DEBUGGING - access to internal arrays.
//
bool Correlation::setXY(uint8_t index, float x, float y)
{
  if (index >= _count) return false;
  _x[index] = x;
  _y[index] = y;
  _needRecalculate = true;
  return true;
}


bool Correlation::setX(uint8_t index, float x)
{
  if (index >= _count) return false;
  _x[index] = x;
  _needRecalculate = true;
  return true;
}


float Correlation::getX(uint8_t index)
{
  if (index >= _count) return NAN;
  return _x[index];
}


bool Correlation::setY(uint8_t index, float y)
{
  if (index >= _count) return false;
  _y[index] = y;
  _needRecalculate = true;
  return true;
}


float Correlation::getY(uint8_t index)
{
  if (index > _count) return NAN;
  return _y[index];
}


float  Correlation::getSumXY()
{
  return _sumXiYi;
}


float  Correlation::getSumX2()
{
  return _sumXi2;
}


float  Correlation::getSumY2()
{
  return _sumYi2;
}


//  -- END OF FILE --

