//
//    FILE: Statistic.cpp
//  AUTHOR: Rob dot Tillaart at gmail dot com
//          modified at 0.3 by Gil Ross at physics dot org
// VERSION: 0.4.3
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
//  HISTORY:
//  0.1     2010-10-29 initial version
//  0.2     2010-10-29 stripped to minimal functionality
//  0.2.01  2010-10-30
//          added minimim, maximum, unbiased stdev,
//          changed counter to long -> int overflows @32K samples
//  0.3     2011-01-07
//          branched from 0.2.01 version of Rob Tillaart's code
//  0.3.1   2012-11-10 minor edits
//  0.3.2   2012-11-10 minor edits
//          changed count -> unsigned long allows for 2^32 samples
//          added variance()
//  0.3.3   2015-03-07
//          float -> double to support ARM (compiles)
//           moved count() sum() min() max() to .h; for optimizing compiler
//  0.3.4   2017-07-31
//          Refactored const in many places
//          [reverted] double to float on request as float is 99.99% of the cases
//          good enough and float(32 bit) is supported in HW for some processors.
//  0.3.5   2017-09-27
//          Added #include <Arduino.h> to fix uint32_t bug
//  0.4.0   2020-05-13
//          refactor
//          Added flag to switch on the use of stdDev runtime. [idea marc.recksiedl]
//  0.4.1   2020-06-19  fix library.json
//  0.4.2   2021-01-08  add Arduino-CI + unit tests
//  0.4.3   2021-01-20  add() returns how much was actually added.


#include "Statistic.h"


Statistic::Statistic(bool useStdDev)
{
  clear(useStdDev);
}


void Statistic::clear(bool useStdDev)	// useStdDev default true.
{
  _cnt = 0;
  _sum = 0;
  _min = 0;
  _max = 0;
  _useStdDev = useStdDev;
  _ssqdif = 0.0;
  // note not _ssq but sum of square differences
  // which is SUM(from i = 1 to N) of f(i)-_ave_N)**2
}


// adds a new value to the data-set
float Statistic::add(const float value)
{
  float previousSum = _sum;
  if (_cnt == 0)
  {
    _min = value;
    _max = value;
  } else {
    if (value < _min) _min = value;
    else if (value > _max) _max = value;
  }
  _sum += value;
  _cnt++;

  if (_useStdDev && (_cnt > 1))
  {
    float _store = (_sum / _cnt - value);
    _ssqdif = _ssqdif + _cnt * _store * _store / (_cnt - 1);

    // ~10% faster but limits the amount of samples to 65K as _cnt*_cnt overflows
    // float _store = _sum - _cnt * value;
    // _ssqdif = _ssqdif + _store * _store / (_cnt*_cnt - _cnt);
    //
    // solution:  TODO verify
    // _ssqdif = _ssqdif + (_store * _store / _cnt) / (_cnt - 1);
  }
  return _sum - previousSum;
}


// returns the average of the data-set added sofar
float Statistic::average() const
{
  if (_cnt == 0) return NAN; // prevent DIV0 error
  return _sum / _cnt;
}


// Population standard deviation = s = sqrt [ S ( Xi - µ )2 / N ]
// http://www.suite101.com/content/how-is-standard-deviation-used-a99084
float Statistic::variance() const
{
  if (!_useStdDev) return NAN;
  if (_cnt == 0) return NAN; // prevent DIV0 error
  return _ssqdif / _cnt;
}


float Statistic::pop_stdev() const
{
  if (!_useStdDev) return NAN;
  if (_cnt == 0) return NAN; // prevent DIV0 error
  return sqrt( _ssqdif / _cnt);
}


float Statistic::unbiased_stdev() const
{
  if (!_useStdDev) return NAN;
  if (_cnt < 2) return NAN; // prevent DIV0 error
  return sqrt( _ssqdif / (_cnt - 1));
}

// -- END OF FILE --
