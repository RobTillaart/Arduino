
[![Arduino CI](https://github.com/RobTillaart/Poisson/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Poisson/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Poisson/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Poisson/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Poisson/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Poisson.svg)](https://github.com/RobTillaart/Poisson/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Poisson/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Poisson.svg?maxAge=3600)](https://github.com/RobTillaart/Poisson/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Poisson.svg)](https://registry.platformio.org/libraries/robtillaart/Poisson)


# Poisson

Arduino library for Poisson distribution math.


## Description

**Experimental**

Poisson is an experimental Arduino library to calculate the probability 
of a Poisson distributed variable.

_The Poisson distribution calculates the probability of a given number 
of events occurring in a fixed interval of time or space, 
provided these events happen at a known constant rate and 
independently of one another._

There are six core functions
- P(X == k)
- P(X <= k) a.k.a. CDF
- P(X <  k)
- P(X >= k)
- P(X >  k)
- P(k1 <= X < k2) === P(X <= k2 - 1) - P(X <= k1)

The library is written for a small experiment, so the library is rather minimal.
Might be useful for educational purposes etc.

Feedback as always is welcome.


### Application example

TODO


### History

See - https://en.wikipedia.org/wiki/Poisson_distribution#History


### Accuracy / precision

The version 0.1.0 uses doubles for internal storage. 
But on many platforms doubles == 4 byte float.
This means precision is at most 6-7 digits.

As the formula uses faculty (k!) the chances drop to zero fast
when the parameter k grows. Also this faculty causes math overflow
quite fast.

Therefore an iterative implementation is used for most functions. 
These are reasonably fast and can handle a wider range of the parameter k.
This parameter is now an uint8_t as for now it is large enough. 
Large values of k (50++) are not tested.

In short there is room for improvement.


### Performance

The functions are optimized as the reference versions were
quite slow. See Poisson_performance.ino.


### Character

|  parameter  |   name   |  ALT-code  |  char |
|:-----------:|:--------:|:----------:|:-----:|
|  mean       |  mu      |  ALT-230   |   µ   |
|  plus minus |          |  ALT-0177  |   ±   |

- https://altcodesguru.com/greek-alt-codes.html


### Related

Backgrounders
- https://en.wikipedia.org/wiki/Normal_distribution
- https://en.wikipedia.org/wiki/Student_distribution
- https://en.wikipedia.org/wiki/Poisson_distribution
- https://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/bs704_probability9.html
- https://stattrek.com/online-calculator/poisson


Related libs
- https://github.com/RobTillaart/Gauss
- https://github.com/RobTillaart/Multimap
- https://github.com/RobTillaart/Statistic more stat links there.
- https://github.com/RobTillaart/Poisson
- https://github.com/RobTillaart/Student
- https://github.com/RobTillaart/PrintHelpers - scientific format.


## Interface

```cpp
#include Poisson.h
```

### Constructor

Note: mu is a.k.a. lambda.

- **Poisson()** constructor, default mu == 1. mu is sometimes called lambda.
- **Poisson(double mu)** constructor.
- **void begin(double mu)** runtime change mu (mean/average).

### P chance

Core functions implemented.

- **double equal(uint8_t k)** P(X == k)
- **double smallerEqual(uint8_t k)** P(X <= k)
- **double smaller(uint8_t k)** P(X <  k)
- **double largerEqual(uint8_t k)** P(X >= k)
- **double larger(uint8_t k)** P(X > k)
- **double between(uint8_t k1, uint8_t k2)** P(k1 <= X < k2)

### Other

- **double average()** idem.
- **double stdev()** idem, returns sqrt(mu).


## Future

#### Must

- documentation
- improve function names.
- test

#### Should

- add examples.
  - performance test
- optimize code(possible?)

#### Could

- add unit tests


#### Won't (unless requested)


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

