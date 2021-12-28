
[![Arduino CI](https://github.com/RobTillaart/Statistic/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml)
[![Arduino-lint](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Statistic/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Statistic/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Statistic.svg?maxAge=3600)](https://github.com/RobTillaart/Statistic/releases)


# Statistic

Statistic library for Arduino includes sum, average, variance and standard deviation.


## Description

The statistic library is made to get basic statistical information from a 
one dimensional set of data, e.g. a stream of values of a sensor.

The stability of the formulas is improved by the help of Gil Ross (Thanks!)


## Interface

- **Statistic(bool useStdDev = true)** Constructor, default use the standard deviation.
functions. Setting this flag to **false** reduces math so slight increase of performance.
- **void clear(bool useStdDev = true)** resets all variables.
- **float add(float value)** (since 0.4.3) returns value actually added to internal sum.
If this is (much) different from what should be added it might become time to call **clear()**.
- **uint32_t count()** returns zero if count == zero (of course).
- **float sum()**      returns zero if count == zero.
- **float minimum()**  returns zero if count == zero.
- **float maximum()**  returns zero if count == zero.
- **float average()**  returns NAN  if count == zero.

These three functions only work if **useStdDev == true**

- **variance()**         returns NAN if count == zero.
- **pop_stdev()**        population stdev, returns NAN if count == zero.
- **unbiased_stdev()**   returns NAN if count == zero.


## Operational

See examples.


## Faq

See faq.md


## Future

- update documentation
  - links that explain statistics in more depth
- derived classes
  - 32 bit with fixed sign version? 
  - 64 bit with fixed sign version?
  - double version?
- create releaseNotes.md

