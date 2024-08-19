//
//    FILE: RunAvgWeight.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-06-30
// PURPOSE: Arduino library to calculate the running average with weights by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunAvgWeight
//
//  based upon: https://github.com/RobTillaart/RunningAverage


#include "RunAvgWeight.h"


RunAvgWeight::RunAvgWeight(const uint16_t size)
{
  _size = size;
  _values = (float*) malloc(_size * sizeof(float));
  _weights = (float *) malloc(_size * sizeof(float));
  if (_values == NULL) _size = 0;
  if (_weights == NULL) _size = 0;
  clear();
}


RunAvgWeight::~RunAvgWeight()
{
  if (_values != NULL) free(_values);
  if (_weights != NULL) free(_weights);
}


//  resets all counters
bool RunAvgWeight::clear()
{
  _count = 0;
  _index = 0;
  _sumValues = 0.0;
  _sumWeights = 0.0;
  _min = NAN;
  _max = NAN;
  if (_size == 0)
  {
    return false;
  }
  for (uint16_t i = 0; i < _size; i++)
  {
    //  setting values and weights to zero keeps addValue simpler
    _values[i] = 0.0;
    _weights[i] = 0.0;
  }
  return true;
}


//  adds a new value to the data-set
bool RunAvgWeight::addValue(const float value, const float weight)
{
  if (_size == 0)
  {
    return false;
  }
  //  TODO weight should be > 0 or at least != 0?

  _sumValues -= _values[_index] * _weights[_index];
  _values[_index] = value;
  _sumValues += _values[_index] * weight;

  _sumWeights -= _weights[_index];
  _weights[_index] = weight;
  _sumWeights += _weights[_index];

  //  update index (next spot to add value).
  _index++;
  if (_index >= _size) _index = 0;  //  faster than %
  //  update count
  if (_count < _size) _count++;
  
  //  handle min max
  if (_count == 1) _min = _max = value;
  else if (value < _min) _min = value;
  else if (value > _max) _max = value;

  return true;
}


float RunAvgWeight::getValue(const uint16_t position)
{
  if (_count == 0)
  {
    return NAN;
  }
  if (position >= _count)
  {
    return NAN;  // cannot ask more than is added
  }
  uint16_t pos = position + _index;
  if (pos >= _count) pos -= _count;
  return _values[pos];
}


//  returns the weight of an element if exist, NAN otherwise
//  "partner" of getValue()
float RunAvgWeight::getWeight(const uint16_t position)
{
  if (_count == 0)
  {
    return NAN;
  }
  if (position >= _count)
  {
    return NAN;  // cannot ask more than is added
  }
  uint16_t pos = position + _index;
  if (pos >= _count) pos -= _count;
  return _weights[pos];
}


//  returns the average of the data-set added so far, NAN if no elements.
float RunAvgWeight::getAverage()
{
  if (_count == 0)
  {
    return NAN;
  }
  //  OPTIMIZE local variable for sums.
  _sumValues = 0;
  _sumWeights = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    _sumValues += _values[i] * _weights[i];
    _sumWeights += _weights[i];
  }
  return _sumValues / _sumWeights;  //  multiplication is faster ==> extra admin
}


//  the larger the size of the internal buffer
//  the greater the gain with respect to getAverage()
float RunAvgWeight::getFastAverage()
{
  if (_count == 0)
  {
    return NAN;
  }

  return _sumValues / _sumWeights;
}


//  What is standard deviation in weighted average context?
//  https://en.wikipedia.org/wiki/Weighted_arithmetic_mean#Weighted_sample_variance
//
//  https://stackoverflow.com/questions/61831353/how-can-i-calculate-weighted-standard-errors-and-plot-them-in-a-bar-plot
//  pop_v = sum( w * (x-mean)^2 ) / sum( w )
//  if the weights are frequency pop_v = sum( w * (x-mean)^2 ) / (sum( w ) - 1)

/*
weighted.var = function(x,w,type="reliability") {
    m=weighted.mean(x,w)
    if(type=="frequency"){ return( sum(w*(x-m)^2)/(sum(w)-1) ) }
    else { return( sum(w*(x-m)^2)*sum(w)/(sum(w)^2-sum(w^2)) ) }
}
weighted.sem = function(x,w,...) { return( sqrt(weighted.var(x,w,...)*sum(w^2)/sum(w)^2) ) }
*/


//  If buffer is empty or has only one element, return NAN.
float RunAvgWeight::getStandardDeviation()
{
  if (_count <= 1) return NAN;

  float average = getFastAverage();
  float variance = 0;
  for (uint16_t i = 0; i < _count; i++)
  {
    float t = _values[i] - average;
    variance += t * t * _weights[i];
  }
  variance /= _sumWeights;
  return sqrt(variance);
}

//  TODO: What is standard error in weighted average context?
//        see above.
//  If buffer is empty or has only one element, return NAN.
float RunAvgWeight::getStandardError()
{
  float temp = getStandardDeviation();
  if (temp == NAN) return NAN;

  float n;
  if (_count >= 30) n = _count;
  else n = _count - 1;
  temp = temp/sqrt(n);

  return temp;
}


//  Return coefficient of variation.
//  If buffer is empty or has only one element or zero average, return NAN.
float RunAvgWeight::getCoefficientOfVariation()
{
  float temp = getStandardDeviation();
  if (temp == NAN) return NAN;
  if (_sumValues == 0) return NAN;

  //  float cv = temp * getFastAverage();
  float cv = temp * _sumWeights / _sumValues;
  return cv;
}


/////////////////////////////////////////////////////////////////////


//  returns the minimum value in the buffer
float RunAvgWeight::getMinInBuffer()
{
  if (_count == 0)
  {
    return NAN;
  }

  float _min = _values[0];
  for (uint16_t i = 1; i < _count; i++)
  {
    if (_values[i] < _min) _min = _values[i];
  }
  return _min;
}


//  returns the maximum value in the buffer
float RunAvgWeight::getMaxInBuffer()
{
  if (_count == 0)
  {
    return NAN;
  }

  float _max = _values[0];
  for (uint16_t i = 1; i < _count; i++)
  {
    if (_values[i] > _max) _max = _values[i];
  }
  return _max;
}


//
//  HELPER FUNCTIONS
//

//  returns the value of an element if exist, NAN otherwise
float RunAvgWeight::getElementValue(const uint16_t index)
{
  if (_count == 0)
  {
    return NAN;
  }
  return _values[index];
}


//  returns the value of an element if exist, NAN otherwise
float RunAvgWeight::getElementWeight(const uint16_t index)
{
  if (_count == 0)
  {
    return NAN;
  }
  return _weights[index];
}


//  -- END OF FILE --

