//
//    FILE: Correlation.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.1
// PURPOSE: Arduino Library to determine correlation between X and Y dataset
//
// HISTORY:
// 0.1.1   2020-06-05 fix library.json
// 0.1.0   2020-05-17 initial version
//

#include "Correlation.h"

Correlation::Correlation()
{
  clear();
}

void Correlation::clear()
{
  _count = 0;
  _idx = 0;
  _needRecalculate = true;
  _runningMode = false;
}

bool Correlation::add(float x, float y)
{
  if (_count < CORRELATION_SIZE || _runningMode)
  {
    _x[_idx] = x;
    _y[_idx] = y;
    _idx++;
    if (_idx >= CORRELATION_SIZE) _idx = 0;
    if (_count < CORRELATION_SIZE) _count++;
    _needRecalculate = true;
    return true;
  }
  return false;
}

bool Correlation::calculate()
{
  if (!_needRecalculate) return true;
  if (_count == 0) return false;

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
  float sumXiYi = 0;
  float sumXi2 = 0;
  float sumYi2 = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    float xi = _x[i] - _avgX;
    float yi = _y[i] - _avgY;
    sumXiYi += (xi * yi);
	sumXi2 += (xi * xi);
	sumYi2 += (yi * yi);
  }
  _b = sumXiYi / sumXi2;
  _a = _avgY - _b * _avgX;
  _rSquare = sumXiYi * sumXiYi / (sumXi2 * sumYi2);

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

// -- END OF FILE --
