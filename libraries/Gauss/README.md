
[![Arduino CI](https://github.com/RobTillaart/Gauss/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Gauss/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Gauss/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Gauss/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Gauss/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Gauss/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Gauss.svg?maxAge=3600)](https://github.com/RobTillaart/Gauss/releases)


# Gauss

Library for the Gauss probability math.


## Description

Gauss is an experimental Arduino library to approximate the probability that a value is 
smaller or larger than a given value.
These under the premises of a Gaussian distribution with parameters **mean** and **stddev** 
(a.k.a. average / mu and standard deviation / sigma).
If these parameters are not given, 0 and 1 are used by default (normalized Gaussian distribution).

The values are approximated with **MultiMap()** using a 32 points interpolated lookup.
Therefore the **MultiMap** library need to be downloaded too (see related below).
The number of lookup points might chance in the future.

Return values are given as floats, if one needs percentages, just multiply by 100.0.


#### Accuracy

The lookup table used has 32 points with 4 significant digits.
Do not expect a higher accuracy / precision.
For many applications this accuracy is sufficient.

(links to a table with more significant digits is welcome).


#### Applications

- use as a filter? do not allow > 3 sigma
- compare historic data to current data
- compare population data with individual


#### Related

- https://en.wikipedia.org/wiki/Normal_distribution
- https://github.com/RobTillaart/Multimap
- https://github.com/RobTillaart/Statistic  (more stat links there).


## Interface

```cpp
#include Gauss.h
```


#### Base

- **Gauss()** constructor. Uses mean = 0 and stddev = 1 by default.
- **bool begin(float mean, float stddev)** set the mean and stddev.
Returns true on success. If needed stddev is made positive.

#### Probability

- **float P_smaller(float f)** returns probability **P(x < f)**.
Multiply by 100.0 to get the value as a percentage.
- **float P_larger(float f)** returns probability **P(x > f)**.
Multiply by 100.0 to get the value as a percentage.
- **float P_between(float f, float g)** returns probability **P(f < x < g)**.
Multiply by 100.0 to get the value as a percentage.
- **float P_equal(float f)** returns probability **P(x == f)**.
This is the bell curve formula.

#### Other

- **float normalize(float f)** normalize a value to normalized distribution.
Is equal to number of **stddevs()**.
- **float stddevs(float f)** returns the number of stddevs from the mean.
E.g if mean == 50 and stddev == 14, then 71 ==> +1.5 sigma.
- **float bellCurve(float f)** returns probability **P(x == f)**.


## Future

#### Must

- documentation
  - mu + sigma character
- unit tests

#### Should

- optimize performance
  - remove division by stddev
- optimize accuracy
  - revisit lookup of MultiMap
  - (-10 .. 0) might be more accurate (significant digits)?
  - double instead of floats? (good table?)



#### Could

- **void setMean(float f)**
- **float getMean()**
- **void setStddev(float f)**
- **float getStddev()**
- default values for **begin(0,1)**
- add examples
  - e.g. temperature (DS18B20 or DHT22)
  - e.g. loadcell (HX711)
- does the stddev needs to be positive, 
  - what happens if negative values are allowed?
- equality test Gauss objects
- move code to .cpp file? (rather small lib).
- embed MultiMap hardcoded instead of library dependency
- **bellCurve()** => **Z()**?


#### Won't (unless requested)


