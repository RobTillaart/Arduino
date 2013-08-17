//
//    FILE: Statistic.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com  
//          modified at 0.3 by Gil Ross at physics dot org
// VERSION: see STATISTIC_LIB_VERSION in .h
// PURPOSE: Recursive statistical library for Arduino
//
// NOTE: 2011-01-07 Gill Ross
// Rob Tillaart's Statistic library uses one-pass of the data (allowing
// each value to be discarded), but expands the Sum of Squares Differences to
// difference the Sum of Squares and the Average Squared. This is susceptible
// to bit length precision errors with the float type (only 5 or 6 digits 
// absolute precision) so for long runs and high ratios of
// the average value to standard deviation the estimate of the 
// standard error (deviation) becomes the difference of two large
// numbers and will tend to zero.
//
// For small numbers of iterations and small Average/SE th original code is
// likely to work fine.
// It should also be recognised that for very large samples, questions 
// of stability of the sample assume greater importance than the
// correctness of the asymptotic estimators.
//
// This recursive algorithm, which takes slightly more computation per
// iteration is numerically stable.
// It updates the number, mean, max, min and SumOfSquaresDiff each step to
// deliver max min average, population standard error (standard deviation) and 
// unbiassed SE.
// -------------
//
// HISTORY:
// 0.1 - 2010-10-29 initial version
// 0.2 - 2010-10-29 stripped to minimal functionality
// 0.2.01 - 2010-10-30
//   added minimim, maximum, unbiased stdev,
//   changed counter to long -> int overflows @32K samples
// 0.3 - 2011-01-07 
//   branched from 0.2.01 version of Rob Tillaart's code
// 0.3.1 - minor edits
// 0.3.2 - 2012-11-10
//   minor edits 
//   changed count -> unsigned long allows for 2^32 samples
//   added variance()
//
// Released to the public domain
//

#include "Statistic.h"

Statistic::Statistic()
{
	clear();
}

// resets all counters
void Statistic::clear()
{ 
	_cnt = 0;
	_sum = 0.0;
	_min = 0.0;
	_max = 0.0;
#ifdef STAT_USE_STDEV
	_ssqdif = 0.0;  // not _ssq but sum of square differences
	                // which is SUM(from i = 1 to N) of 
                    // (f(i)-_ave_N)**2
#endif
}

// adds a new value to the data-set
void Statistic::add(float f)
{
	if (_cnt == 0)
	{
		_min = f;
		_max = f;
	} else {
		if (f < _min) _min = f;
		if (f > _max) _max = f;           
    }
	_sum += f;
	_cnt++;
	
#ifdef STAT_USE_STDEV 
    if (_cnt >1) 
	{
	    _store = (_sum / _cnt - f);
        _ssqdif = _ssqdif + _cnt * _store * _store / (_cnt-1);
    } 
#endif
}

// returns the number of values added
unsigned long Statistic::count()
{
	return _cnt;
}

// returns the average of the data-set added sofar
float Statistic::average()
{
	if (_cnt == 0) return NAN; // original code returned 0
	return _sum / _cnt;
}

// returns the sum of the data-set (0 if no values added)
float Statistic::sum()
{
	return _sum;
}

// returns the sum of the data-set (0 if no values added)
float Statistic::minimum()
{
	return _min;
}

// returns the sum of the data-set (0 if no values added)
float Statistic::maximum()
{
	return _max;
}


// Population standard deviation = s = sqrt [ S ( Xi - � )2 / N ]
// http://www.suite101.com/content/how-is-standard-deviation-used-a99084
#ifdef STAT_USE_STDEV  

float Statistic::variance()
{
	if (_cnt == 0) return NAN; // otherwise DIV0 error
	return _ssqdif / _cnt;
}

float Statistic::pop_stdev()
{
	if (_cnt == 0) return NAN; // otherwise DIV0 error
	return sqrt( _ssqdif / _cnt);
}

float Statistic::unbiased_stdev()
{
	if (_cnt < 2) return NAN; // otherwise DIV0 error
	return sqrt( _ssqdif / (_cnt - 1));
}

#endif
// END OF FILE