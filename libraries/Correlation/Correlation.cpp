//
//    FILE: Correlation.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino Library to determine correlation between X and Y dataset
//
//  HISTORY:
//  0.1.3  2021-01-16  add size in constructor, 
//                     add statistical + debug functions
//  0.1.2  2020-12-17  add arduino-CI + unit tests
//                     + size() + getAvgX() + getAvgY()
//  0.1.1  2020-06-05  fix library.json
//  0.1.0  2020-05-17  initial version



#include "Correlation.h"


Correlation::Correlation(uint8_t size)
{
  _size = size;
  _x = (float *) malloc(_size * sizeof(float));
  _y = (float *) malloc(_size * sizeof(float));
  clear();
}


Correlation::~Correlation()
{
  free(_x);
  free(_y);
}


void Correlation::clear()
{
  _count           = 0;
  _idx             = 0;
  _needRecalculate = true;
  _runningMode     = false;
  _avgX            = 0;
  _avgY            = 0;
  _a               = 0;
  _b               = 0;
  _rSquare         = 0;
  _sumErrorSquare  = 0;
  _sumXiYi         = 0;
  _sumXi2          = 0;
  _sumYi2          = 0;
}


bool Correlation::add(float x, float y)
{
  if ( (_count < _size) || _runningMode)
  {
    _x[_idx] = x;
    _y[_idx] = y;
    _idx++;
    if (_idx >= _size) _idx = 0;
    if (_count < _size) _count++;
    _needRecalculate = true;
    return true;
  }
  return false;
}


bool Correlation::calculate()
{
  if (_count == 0) return false;
  if (!_needRecalculate) return true;

  // CALC AVERAGE X, AVERAGE Y
  _avgX = 0;
  _avgY = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    _avgX += _x[i];
    _avgY += _y[i];
  }
  _avgX /= _count;
  _avgY /= _count;

  // CALC A and B  ==>  formula  Y = A + B*X
  _sumXiYi = 0;
  _sumXi2  = 0;
  _sumYi2  = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    float xi = _x[i] - _avgX;
    float yi = _y[i] - _avgY;
    _sumXiYi += (xi * yi);
    _sumXi2  += (xi * xi);
    _sumYi2  += (yi * yi);
  }
  _b = _sumXiYi / _sumXi2;
  _a = _avgY - _b * _avgX;
  _rSquare = _sumXiYi * _sumXiYi / (_sumXi2 * _sumYi2);

  // CALC _sumErrorSquare
  _sumErrorSquare = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    float EY =  _a + _b * _x[i];
    float ei = _y[i] - EY;
    _sumErrorSquare += (ei * ei);
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
  return (y - _a) / _b;
}


//////////////////////////////////////////////////////
//
// STATISTICAL
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
// DEBUGGING - access to internal arrays.
//
bool Correlation::setXY(uint8_t idx, float x, float y)
{
  if (idx >= _count) return false;
  _x[idx] = x;
  _y[idx] = y;
  _needRecalculate = true;
  return true;
}

bool Correlation::setX(uint8_t idx, float x)
{
  if (idx >= _count) return false;
  _x[idx] = x;
  _needRecalculate = true;
  return true;
}

float Correlation::getX(uint8_t idx)
{
  if (idx >= _count) return NAN;
  return _x[idx];
}

bool Correlation::setY(uint8_t idx, float y)
{
  if (idx >= _count) return false;
  _y[idx] = y;
  _needRecalculate = true;
  return true;
}

float Correlation::getY(uint8_t idx)
{
  if (idx > _count) return NAN;
  return _y[idx];
}

// -- END OF FILE --
