//
//    FILE: histogram.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com  
// VERSION: see HISTOGRAM_LIB_VERSION in .h
// PURPOSE: Histogram library for Arduino
//
// HISTORY:
// 0.1.0 - 2012-11-10 initial version
// 0.1.1 - 2012-11-10 added PMF() and CDF()
// 0.1.2 - 2012-12-23 changed float to double; some comments
//
// Released to the public domain
//

#include "histogram.h"

Histogram::Histogram(uint8_t len, double *bounds)
{
	_bounds = bounds;
	_len = len;
	_data = (long*) malloc((len+1) * sizeof(long)); 
	clear();
}

Histogram::~Histogram()
{
	free(_data);  // free may still has a bug :(
}

// resets all counters
void Histogram::clear()
{ 
	for (uint8_t i = 0; i < _len+1; i++)
	{
		_data[i] = 0;
	}
	_cnt = 0;
}

// adds a new value to the histogram - increasing
void Histogram::add(double f)
{
	_data[find(f)]++;
	_cnt++;
}

// adds a new value to the histogram - decreasing
void Histogram::sub(double f)
{
	_data[find(f)]--;
	_cnt++;;
}

// returns the number of buckets
uint8_t Histogram::size()
{
	return _len+1;
}

// returns the number of values added
unsigned long Histogram::count()
{
	return _cnt;
}

// returns the count of a bucket
long Histogram::bucket(uint8_t idx)
{
	if (idx > _len+1) return 0;
	return _data[idx];
}

// returns the relative frequency of a bucket
double Histogram::frequency(uint8_t idx)
{
	if (_cnt == 0) return NAN;
	if (idx > _len+1) return 0;
	return (1.0 * _data[idx]) / _cnt;
}

// returns the probability of the bucket of a value
double Histogram::PMF(double val)
{
	if (_cnt == 0) return NAN;
	uint8_t idx = find(val);
	return (1.0 *_data[idx]) / _cnt;
}

// returns the cummulative probability of 
// values <= value
double Histogram::CDF(double val)
{
	if (_cnt == 0) return NAN;
	uint8_t idx = find(val);
	long sum = 0;
	for (uint8_t i=0; i<= idx; i++) sum += _data[i];
	return (1.0 * sum) / _cnt;
}

// EXPERIMENTAL
// returns the value of the original array for 
// which the CDF is at least prob.
double Histogram::VAL(double prob)
{
	if (_cnt == 0) return NAN;
	if (prob < 0.0) prob = 0.0;
	if (prob > 1.0) prob = 1.0;
	
	long sum = 0;
	for (uint8_t i = 0; i <= _len; i++)
	{
		sum += _data[i];
		if (sum >= (prob * _cnt)) return _bounds[i];
	}
	return INFINITY;
}

// returns the bucket number for value f
uint8_t Histogram::find(double f)
{
	uint8_t i = 0;
	while(i < _len && f > _bounds[i]) i++;
	return i;
}

// END OF FILE