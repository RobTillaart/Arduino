#pragma once
//
//    FILE: Statistic.h
//  AUTHOR: Rob Tillaart
//          modified at 0.3 by Gil Ross at physics dot org
//          template version 1.0.0 by Glen Cornell
// VERSION: 1.0.8
// PURPOSE: Recursive Statistical library for Arduino
// HISTORY: See CHANGELOG.md
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
// For small numbers of iterations and small Average/SE the original code is
// likely to work fine.
// It should also be recognised that for very large samples, questions
// of stability of the sample assume greater importance than the
// correctness of the asymptotic estimators.
//
// This recursive algorithm, which takes slightly more computation per
// iteration is numerically stable.
// It updates the number, mean, max, min and SumOfSquaresDiff each step to
// deliver max min average, population standard error (standard deviation) and
// unbiased SE.

// Toolchains for some platforms don't have the stdc++ library, so
// we'll make substitutions for features that we use.  If your
// platform isn't specified here and fails to compile, then you can
// explicitly override the HAVE_STDCXX_TYPE_TRAITS, HAVE_STDCXX_CMATH,
// and HAVE_STDCXX_CSTDINT feature macros in your build environment.


#define STATISTIC_LIB_VERSION                     (F("1.0.8"))


#if defined(__AVR__)
#define HAVE_STDCXX_TYPE_TRAITS 0
#define HAVE_STDCXX_CMATH 0
#define HAVE_STDCXX_CSTDINT 0
#else
#ifndef HAVE_STDCXX_TYPE_TRAITS
#define HAVE_STDCXX_TYPE_TRAITS 1
#endif
#ifndef HAVE_STDCXX_CMATH
#define HAVE_STDCXX_CMATH 1
#endif
#ifndef HAVE_STDCXX_CSTDINT
#define HAVE_STDCXX_CSTDINT 1
#endif
#endif


#if HAVE_STDCXX_TYPE_TRAITS || defined(_GLIBCXX_TYPE_TRAITS)
#include <type_traits>
#else
namespace std {
  //  substitute for std::conditional if not in your tool chain
  template<bool B, class T, class F>
  struct conditional { typedef T type; };
  template<class T, class F>
  struct conditional<false, T, F> { typedef F type; };
};
#endif  /*  HAVE_STDCXX_TYPE_TRAITS */


#if HAVE_STDCXX_CMATH || defined(_GLIBCXX_CMATH)
#include <cmath>
#if not defined(__cplusplus) || __cplusplus < 201703L
//  substitute for std::sqrtf function, patch for issue #13
#undef sqrtf
namespace std {
  inline float sqrtf(float n) { return __builtin_sqrtf(n); }
};
#endif
#else
#include <math.h>
//  substitute for std::sqrt functions if not in your tool chain
#undef sqrt
namespace std {
  inline float sqrt(float n) { return __builtin_sqrtf(n); }
  inline double sqrt(double n) { return __builtin_sqrt(n); }
  inline long double sqrt(long double n) { return __builtin_sqrtl(n); }
};
#endif  /*  HAVE_STDCXX_CMATH */


#if HAVE_STDCXX_CSTDINT || defined(_GLIBCXX_CSTDINT)
#include <cstdint>
#else
#include <stdint.h>  //  uint32_t, etc.
#endif  /*  HAVE_STDCXX_CSTDINT */


#if HAVE_STDCXX_LIMITS || defined(_GLIBCXX_NUMERIC_LIMITS)
#include <limits>
#else
namespace std {
  template<typename T>
  struct numeric_limits {
    static constexpr T
    quiet_NaN() { return T(); }
  };
  template<>
  struct numeric_limits<float> {
    static constexpr float
    quiet_NaN() { return __builtin_nanf(""); }
  };
  template<>
  struct numeric_limits<double> {
    static constexpr double
    quiet_NaN() { return __builtin_nan(""); }
  };
  template<>
  struct numeric_limits<long double> {
    static constexpr long double
    quiet_NaN() { return __builtin_nanl(""); }
  };
};
#endif /* HAVE_STDCXX_LIMITS */


///////////////////////////////////////////////////////////////////////////////
//
//  STATISTICS CLASS
//

namespace statistic {

template <typename T = float, typename C = uint32_t, bool _useStdDev = true>
class Statistic
{
public:
  typedef T value_type;
  typedef C count_type;

  static constexpr value_type NaN { std::numeric_limits<value_type>::quiet_NaN() };

  Statistic() = default;


  void clear() {
    _cnt = 0;
    _sum = 0;  //  NaN;
    _min = 0;  //  NaN;
    _max = 0;  //  NaN;
    _extra.clear();
    //  NOTE: _extra "guards" the conditional code e.g. ssqdiff
    //  NOTE: ssqdiff = not _ssq but sum of square differences
    //  which is SUM(from i = 1 to N) of f(i)-_ave_N)**2
  }


  //  returns value actually added
  value_type add(const value_type value) {
    value_type previousSum = _sum;
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
      value_type _store = (_sum / _cnt - value);
      _extra.ssqdif(_extra.ssqdif() + _cnt * _store * _store / (_cnt - 1));

      //  NOTE: pre 1.0.0 code
      //  ~10% faster but limits the amount of samples to 65K as _cnt*_cnt overflows
      //  value_type _store = _sum - _cnt * value;
      //  _ssqdif = _ssqdif + _store * _store / (_cnt*_cnt - _cnt);
      //
      //  solution:  TODO verify
      //  _ssqdif = _ssqdif + (_store * _store / _cnt) / (_cnt - 1);
    }
    return _sum - previousSum;
  }


  //  returns the number of values added
  count_type count() const   { return _cnt; };   //  zero if count == zero
  value_type sum() const     { return _sum; };   //  zero if count == zero
  value_type minimum() const { return _min; };   //  zero if count == zero
  value_type maximum() const { return _max; };   //  zero if count == zero
  value_type range() const   { return _max - _min; };   //  zero if count == zero
  value_type middle() const
  {
    //  prevent over- or underflow if value_type is an int type
    double mid = _max * 0.5 + _min * 0.5;
    return (value_type) mid;
  };   //  zero if count == zero


  //  NAN if count == zero
  value_type average() const {
    if (_cnt == 0) return NaN;  //  prevent DIV0 error
    return _sum / _cnt;
  }


  //  useStdDev must be true to use next three
  //  all return NAN if count == zero
  value_type variance() const {
    if (!_useStdDev) return NaN;
    if (_cnt == 0) return NaN;  //  prevent DIV0 error
    return _extra.ssqdif() / _cnt;
  }


  // Population standard deviation
  value_type pop_stdev() const {
    if (!_useStdDev) return NaN;
    if (_cnt == 0) return NaN;  //  prevent DIV0 error
    return std::sqrt( _extra.ssqdif() / _cnt);
  }


  value_type unbiased_stdev() const {
    if (!_useStdDev) return NaN;
    if (_cnt < 2) return NaN;  //  prevent DIV0 error
    return std::sqrt( _extra.ssqdif() / (_cnt - 1));
  }

  value_type getCoefficientOfVariation() const {
    if (_sum == 0) return NaN;
    value_type temp = pop_stdev();  //  as all samples are available
    if (temp == NaN) return NaN;
    //  return standard deviation / average
    value_type cv = temp * _cnt / _sum;
    return cv;
  }

  //  deprecated methods:
  Statistic(bool) {
  } __attribute__ ((deprecated ("use default constructor instead")));
  void clear(bool) {
    clear();
  } __attribute__ ((deprecated ("use Statistic::clear(void) instead")));


protected:
  count_type _cnt { 0 };
  value_type _sum { 0.0 };   //  NaN;
  value_type _min { 0.0 };   //  NaN;
  value_type _max { 0.0 };   //  NaN;


  //  Conditionally compile to reduce dead code if not used
  struct Empty {
    void clear() { }
    value_type ssqdif() const { return NaN; }
    void ssqdif(value_type v) { }
  };


  struct StdDev {
    value_type    _ssqdif { 0.0 };    //  sum of squares difference
    void clear() { _ssqdif = 0.0; }
    value_type ssqdif() const { return _ssqdif; }
    void ssqdif(value_type v) { _ssqdif = v; }
  };


  typename std::conditional<_useStdDev, StdDev, Empty>::type _extra;
};

} //  namespace statistic


//  This typedef maintains backwards API compatibility with library
//  versions <= 0.4.4.
typedef statistic::Statistic<float, uint32_t, true> Statistic;


//  NOTE: Do not issue 'using statistic;' in your code because the
//  compiler will not be able to distinguish between the template
//  '::Statistic' and the typedef 'statistic::Statistic'


//  -- END OF FILE --

