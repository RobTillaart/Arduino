
[![Arduino CI](https://github.com/RobTillaart/Gauss/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Gauss/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Gauss/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Gauss/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Gauss/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Gauss.svg)](https://github.com/RobTillaart/Gauss/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Gauss/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Gauss.svg?maxAge=3600)](https://github.com/RobTillaart/Gauss/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Gauss.svg)](https://registry.platformio.org/libraries/robtillaart/Gauss)


# Gauss

Library for the Gauss probability math. (Normal Distribution).


## Description

Gauss is an experimental Arduino library to approximate the probability that a value is 
smaller or larger than a given value.
These under the premises of a Gaussian distribution with parameters **mean** and **stddev** 
(a.k.a. average / mu / µ and standard deviation / sigma / σ).
If these parameters are not given, mean == 0 and stddev == 1 are used by default.
This is the normalized Gaussian distribution.

The values of the functions are approximated with a **MultiMap()** based lookup 
using a 34 points interpolated lookup. 
- Version 0.1.x used the **MultiMap** library need to be downloaded too (see related below).
- Version 0.2.0 and above embeds an optimized version, so no need to use **MultiMap**.

Note: The number of lookup points might chance in the future, keeping a balance between
accuracy and footprint.


#### Accuracy / precision

The version 0.2.0 lookup table has 34 points with 8 decimals. 
This matches the precision of float data type.
Do not expect an 8 decimals accuracy / precision as interpolation is linear.

A first investigation (part 0.0 - 1.3) shows:
- maximum error ~ 0.0003016 <= 0.031%
- average error ~ 0.0001433 <= 0.015%

I expect that for many applications this accuracy is probably sufficient.

The 34 points are in a (mostly) equidistant table.
Searching the interpolation points is optimized in version 0.2.0.
The table uses the symmetry of the distribution to reduce the number of points.

Values of the table are calculated with ```NORM.DIST(x, mean, stddev, true)```
spreadsheet function.

Note: 0.1.0 was 32 points 4 decimals. Need to investigate reduction of points.


#### Applications

- use as a filter e.g. detect above N1 sigma and under N2 sigma
- compare historic data to current data e.g. temperature.
  - transforming to sigma makes it scale C / F / K independent.
- fill a bag (etc) until a certain weight is reached (+- N sigma)
- compare population data with individual, e.g. Body Mass Index (BMI).


#### Character

|  parameter  |  name  |  ALT-code  |  char |
|:-----------:|:------:|:----------:|:-----:|
|  mean       |  mu    |  ALT-230   |   µ   |
|  stddev     | sigma  |  ALT-229   |   σ   |
|  CDF        |  phi   |  ALT-232   |   Φ   |  ALT-237 for lower case

- https://altcodesguru.com/greek-alt-codes.html


#### Related

- https://en.wikipedia.org/wiki/Normal_distribution
- https://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/bs704_probability9.html
- https://github.com/RobTillaart/Multimap
- https://github.com/RobTillaart/Statistic  (more stat links there).


## Interface

```cpp
#include Gauss.h
```


#### Base

- **Gauss()** constructor. Uses mean = 0 and stddev = 1 by default.
- **bool begin(float mean = 0, float stddev = 1)** set the mean and stddev.
Returns true if stddev > 0 which should be so.
Returns false if stddev <= 0, however it could be a user choice to use this.
Note that if ```stddev == 0```, probabilities cannot be calculated 
as the distribution is not Gaussian.
The default values (0, 1) gives the normalized Gaussian distribution.
**begin()** can be called at any time to change the mean and/or stddev.
- **float getMean()** returns current mean.
- **float getStddev()** returns current stddev.


#### Probability

Probability functions return NAN if stddev == 0.  
Return values are given as a float 0.0 .. 1.0.  
Multiply probabilities by 100.0 to get the value as a percentage.

- **float P_smaller(float f)** returns probability **P(x < f)**.
A.k.a. **CDF()** Cumulative Distribution Function.
- **float P_larger(float f)** returns probability **P(x > f)**.
As the distribution is continuous **P_larger(f) == 1 - P_smaller(f)**.
- **float P_between(float f, float g)** returns probability **P(f < x < g)**.
  - if f >= g ==> returns 1.0
- **float P_equal(float f)** returns probability **P(x == f)**.
This uses the bell curve formula.
- **float P_outside(float f, float g)** returns probability **P(x < f) + P(g < x)**.
  - note that f should be smaller or equal to g
  - **P_outside() = 1 - P_between()**


#### Normalize

- **float normalize(float f)** normalize a value to normalized distribution.
E.g if mean == 50 and stddev == 14, then 71 ==> +1.5 sigma.
Is equal to number of **stddevs()**.
- **float denormalize(float f)** reverses normalize(). 
What value would have a deviation of 1.73 stddev.
- **float stddevs(float f)** returns the number of stddevs from the mean.
Identical to **normalize()**.


#### Other

wrapper functions:

- **float bellCurve(float f)** returns probability **P(x == f)**.
- **float CDF(float f)** returns probability **P(x < f)**.


## Performance

Indicative numbers for 1000 calls, timing in micros.

Arduino UNO, 16 MHz, IDE 1.8.19

|  function     |  0.1.0   |  0.1.1   |  0.2.0   |  notes  |
|:--------------|:--------:|:--------:|:--------:|:--------|
|  P_smaller    |  375396  |  365964  |  159536  |
|  P_larger     |  384368  |  375032  |  169056  |
|  P_between    |  265624  |  269176  |  150148  |
|  normalize    |   44172  |   23024  |   23024  |
|  bellCurve    |  255728  |  205460  |  192524  |
|  approx.bell  |  764028  |  719184  |  333172  |  see examples 


ESP32, 240 MHz, IDE 1.8.19

|  function     |  0.1.0   |  0.1.1   |  0.2.0   |  notes  |
|:--------------|:--------:|:--------:|:--------:|:--------|
|  P_smaller    |    -     |    4046  |    1498  |
|  P_larger     |    -     |    4043  |    1516  |
|  P_between    |    -     |    3023  |    1569  |
|  normalize    |    -     |     592  |     585  |
|  bellCurve    |    -     |   13522  |   13133  |
|  approx.bell  |    -     |    7300  |    2494  | 


## Future

#### Must

- documentation
- test test test

#### Should


#### Could

- add examples
- add unit tests
- **VAL(probability = 0.75)** ==>  134 whatever
  - Returns the value for which the **CDF()** is at least probability.
  - Inverse of **P_smaller()** (how? binary search)
  

#### Won't (unless requested)

- equality test Gauss objects
- does the stddev needs to be positive? Yes.
  - what happens if negative values are allowed? P curve is reversed.
- move code to .cpp file? (rather small lib).
- **void setMean(float f)** can be done with begin()
- **void setStddev(float f)** can be done with begin()
- optimize accuracy
  - (-6 .. 0) might be more accurate (significant digits)?


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

