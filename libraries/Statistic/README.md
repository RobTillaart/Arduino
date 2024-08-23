
[![Arduino CI](https://github.com/RobTillaart/Statistic/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Statistic/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Statistic/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Statistic.svg)](https://github.com/RobTillaart/Statistic/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Statistic/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Statistic.svg?maxAge=3600)](https://github.com/RobTillaart/Statistic/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Statistic.svg)](https://registry.platformio.org/libraries/robtillaart/Statistic)


# Statistic

Header-only statistic library for Arduino includes sum, average, variance and standard deviation.

The `statistic::Statistic<T, C, bool _useStdDev>` class template accepts 3 arguments:

* **`typename T`:** The floating point type used to represent the statistics.
* **`typename C`:** The unsigned integer type to store the number of values.
* **`typename _useStdDev`:** Compile-time flag for using variance and standard deviation.

To maintain backwards compatibility with API <= 0.4.4, the `Statistic`
class implementation has been moved to the `statistic` namespace and a
`typedef statistic::Statistic<float, uint32_t, true> Statistic` type
definition has been created at global scope.

The `useStdDev` boolean was moved from a run-time to a compile-time
option for two reasons.  First, the compile-time option allows the
optimizer to eliminate dead code (calculating standard deviation and
variances) for a slightly smaller code size.  Second, it was observed
in uses of the library that the `useStdDev` boolean was set once in
the class constructor and was never modified at run-time.


## Description

The statistic library is made to get basic statistical information from a 
one dimensional set of data, e.g. a stream of values of a sensor.

The stability of the formulas is improved by the help of Gil Ross (Thanks!).

The template version (1.0.0) is created by Glen Cornell  (Thanks!).


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic
- https://github.com/RobTillaart/Student


## Interface

```cpp
#include "Statistic.h"
```

#### Constructor

- **Statistic(void)** Default constructor.
- **statistic::Statistic<float, uint32_t, true>** Constructor, with value type, count type, and standard deviation flag.
The types mentioned are the defaults of the template. 
You can override e.g. **statistic::Statistic<double, uint64_t, false>** for many high precision values. 
(assumes double >> float).
- **void clear()** resets all internal variables and counters.


#### Core

- **typename T add(const typename T value)** returns value actually added to internal sum.
If this differs from what should have been added, or even zero, the internal administration is running out of precision.
If this happens after a lot of **add()** calls, it might become time to call **clear()**.
Alternatively one need to define the statistic object with a more precise data type (typical double instead of float).
- **typename C count()**    returns zero if count == zero (of course). Must be checked to interpret other values.
- **typename T sum()**      returns zero if count == zero.
- **typename T minimum()**  returns zero if count == zero.
- **typename T maximum()**  returns zero if count == zero.
- **typename T range()**    returns maximum - minimum. 
- **typename T middle()**   returns (minimum + maximum)/2. If T is an integer type rounding errors are possible.
- **typename T average()**  returns NAN if count == zero.

These three functions only work if **useStdDev == true** (in the template).

- **typename T variance()**      returns NAN if count == zero.
- **typename T pop_stdev()**     returns NAN if count == zero.
pop_stdev = population standard deviation, 
- **typename T unbiased_stdev()** returns NAN if count == zero.
- **typename T getCoefficientOfVariation()** returns coefficient of variation.
This is defined as standardDeviation / Average. 
It indicates if the distribution is relative small ( < 1) or relative wide ( > 1).
Note it has no meaning when the average is zero (or close to zero).


#### Deprecated methods

- **Statistic(bool)** Constructor previously used to enable/disable the standard deviation functions. 
This argument now has no effect.  It is recommended to migrate your code to the default constructor 
(which now also implicitly calls `clear()`).
- **void clear(bool)** resets all variables.  The boolean argument is ignored. 
It is recommended to migrate your code to `clear()` (with no arguments).


#### Range() and middle()

**Range()** and **middle()** are fast functions with limited statistical value. 
Still they have their uses.

Given enough samples (e.g. 100+) and a normal distribution of the samples the **range()** is expected 
to be 3 to 4 times the **pop_stdev()**. 
If the range is larger than 4 standard deviations one might have added one or more outliers.

Given enough samples (e.g. 100+) and a normal distribution, the **middle()** and **average()** are 
expected to be close to each other.
Note: outliers can disrupt the **middle()**, Several non-normal distributions do too.


## Operational

See examples.


## Faq

See https://github.com/RobTillaart/Statistic/blob/master/FAQ.md


## Future

#### Must

- update documentation
  - links that explain statistics in more depth

#### Should

- remove deprecated methods. (1.1.0)

#### Could

- add **expected average EA** compensation trick
  - every add will subtract EA before added to sum, 
  - this will keep the **\_sum** to around zero.
  - this will move **average()** to around zero.
  - do not forget to add **EA** to average.
  - do not forget to add **EA** times count for sum.
  - does not affect the **std_dev()**
  - all functions will become slightly slower.
  - maybe in a derived class?
- **lastTimeAdd()** convenience, user can track timestamp
- **largestDelta()** largest difference between two consecutive additions.
  - need lastValue + delta so far.

#### Wont

- return values of **sum(), minimum(), maximum()** when **count()** == zero
  - should these be NaN, which is technically more correct?
  - does it exist for all value types? => No!
  - user responsibility to check **count()** first.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

