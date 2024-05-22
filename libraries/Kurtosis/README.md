
[![Arduino CI](https://github.com/RobTillaart/Kurtosis/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Kurtosis/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Kurtosis/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Kurtosis/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Kurtosis/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Kurtosis.svg)](https://github.com/RobTillaart/Kurtosis/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Kurtosis/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Kurtosis.svg?maxAge=3600)](https://github.com/RobTillaart/Kurtosis/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Kurtosis.svg)](https://registry.platformio.org/libraries/robtillaart/Kurtosis)


# Kurtosis

Arduino library for calculating skewness and kurtosis of a dataset  (statistics).


## Description

**Experimental**

This library was written after a request how to calculate the kurtosis of a histogram.
Diving into this question I learned Kurtosis is a statistical measurements, somewhat 
related to the skewness ("is balanced") of that dataset.

Not a statistician by profession, I searched the internet and found several sources 
that described the kurtosis measurement.
The code of this library is based upon the code of **John D. Cook** in the blog named 
"Computing skewness and kurtosis in one pass".
See - https://www.johndcook.com/blog/skewness_kurtosis/

I adapted the code on a few places to improve performance a bit.
Furthermore I named the library Kurtosis as calculating that is the 
prime purpose of this library.

For a deep technical reader about kurtosis and skewness I refer to the Wikipedia.

Links to other information is welcome.


#### Related

- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/Kurtosis
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/Statistic
- https://en.wikipedia.org/wiki/Skewness
- https://en.wikipedia.org/wiki/Kurtosis


## Performance

Time in us, platform UNO, 

0.0.0 is non optimized version.

|  function  |  0.0.0  |  0.1.0  |  Notes  |
|:----------:|:-------:|:-------:|:-------:|
|  add       |   232   |   212   |
|  variance  |    -    |    44   |
|  skewness  |   416   |   352   |
|  kurtosis  |    -    |    64   |


## Interface

```cpp
#include "Kurtosis.h"
```

#### Base

- **Kurtosis()** create the Kurtosis object.
- **void reset()** resets the internal variables.
- **void add(double x)** add new value to the internal variables.

- **uint32_t count()** returns the amount of values added.
- **double mean()** returns the mean (or average) of the values added. 
This function will return 0 if no values have been added, or after reset().
- **double variance()** idem.
Note this value is cached as **stddev()** uses it too. 
So the performance of two consecutive calls differ in duration.
- **double stddev()** standard deviation.
- **double skewness()** returns skewness ("balanced"), negative values indicate left skew, 
positive values indicate right skew. See Wikipedia for details.
- **double kurtosis()** returns the kurtosis, "tailedness" is used e.g. to detect outliers.
See Wikipedia for details.


## Future


#### Must

- improve documentation.
- understand the math in more detail.

#### Should

- extend unit tests.
- add examples to explain the purpose.

#### Could

- cache skewness and kurtosis? useful?

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

