
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
(a.k.a. average / mu / µ and standard deviation / sigma / σ).
If these parameters are not given, 0 and 1 are used by default (normalized Gaussian distribution).

The values are approximated with **MultiMap()** using a 32 points interpolated lookup.
Therefore the **MultiMap** library need to be downloaded too (see related below).
The number of lookup points might chance in the future.

Return values are given as floats, if one needs percentages, just multiply by 100.0.


#### Accuracy

The lookup table has 34 points with 8 decimals.  
This matches the precision of float data type.
Do not expect a very high accuracy / precision as interpolation is linear.
For many applications this accuracy is sufficient.

Values of the table are calculated with ```NORM.DIST(mean, stddev, x, true)```.

Note: 0.1.0 was 32 points 4 decimals. Need to investigate reduction of points.

#### Applications

- use as a filter? do not allow > 3 sigma
- compare historic data to current data
- compare population data with individual


#### Character

|  parameter  |  name  |  ALT-code  |  char |
|:-----------:|:------:|:----------:|:-----:|
|  mean       |  mu    |  ALT-230   |   µ   |
|  stddev     | sigma  |  ALT-229   |   σ   |

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
Returns false if stddev <= 0, which could be a user choice.
Note that if ```stddev == 0```, probabilities cannot be calculated 
as the distribution is not Gaussian.
The default values (0,1) gives the normalized Gaussian distribution.
**begin()** can be called at any time to change the mean or stddev.
- **float getMean()** returns current mean.
- **float getStddev()** returns current stddev.


#### Probability

Probability functions return NAN if stddev == 0.

- **float P_smaller(float f)** returns probability **P(x < f)**.
Multiply by 100.0 to get the value as a percentage.
A.k.a. **CDF()** Cumulative Distribution Function.
- **float P_larger(float f)** returns probability **P(x > f)**.
Multiply by 100.0 to get the value as a percentage.
As the distribution is continuous **P_larger(f) == 1 - P_smaller(f)**.
- **float P_between(float f, float g)** returns probability **P(f < x < g)**.
Multiply by 100.0 to get the value as a percentage.
- **float P_equal(float f)** returns probability **P(x == f)**.
This uses the bell curve formula.


#### Other

- **float normalize(float f)** normalize a value to normalized distribution.
Is equal to number of **stddevs()**.
- **float stddevs(float f)** returns the number of stddevs from the mean.
E.g if mean == 50 and stddev == 14, then 71 ==> +1.5 sigma.
- **float bellCurve(float f)** returns probability **P(x == f)**.


## Performance

Indicative numbers for 1000 calls, timing in micros.

Arduino UNO, 16 MHz, IDE 1.8.19

|  function     |  0.1.0   |  0.1.1   |  notes  |
|:--------------|:--------:|:--------:|:--------|
|  P_smaller    |  375396  |  365964  |
|  P_larger     |  384368  |  375032  |
|  P_between    |  265624  |  269176  |
|  normalize    |   44172  |   23024  |
|  bellCurve    |  255728  |  205460  |
|  approx.bell  |  764028  |  719184  |  see examples 


ESP32, 240 MHz, IDE 1.8.19

|  function     |  0.1.0   |  0.1.1   |  notes  |
|:--------------|:--------:|:--------:|:--------|
|  P_smaller    |    -     |    4046  |
|  P_larger     |    -     |    4043  |
|  P_between    |    -     |    3023  |
|  normalize    |    -     |     592  |
|  bellCurve    |    -     |   13522  |
|  approx.bell  |    -     |    7300  | 


## Future

#### Must

- documentation


#### Should

- optimize accuracy
  - revisit lookup of MultiMap
  - (-10 .. 0) might be more accurate (significant digits)?
  - double instead of floats? (good table?)
  - make use of equidistant \_\_z\[] table


#### Could

- add examples
  - e.g. temperature (DS18B20 or DHT22)
  - e.g. loadcell (HX711)
- embed MultiMap hardcoded instead of library dependency
- add unit tests
- remove **\_stddev** as **\_reciprokeSD** holds same information.
- reverse normalization
  - G(100,25) which value has stddev 0.735?
- **VAL(probability = 0.75)** ==>  134 whatever
  - Returns the value of the distribution for which the **CDF()** is at least probability.
  - Inverse of **P_smaller()**
- **float P_outside(float f, float g)** returns probability **P(x < f) + P(g < x)**.
  - assuming no overlap. Use **P_outside() = 1 - P_between()**


#### Won't (unless requested)

- equality test Gauss objects
- does the stddev needs to be positive? Yes.
  - what happens if negative values are allowed? P curve is reversed.
- move code to .cpp file? (rather small lib).
- **void setMean(float f)** can be done with begin()
- **void setStddev(float f)** can be done with begin()


