
[![Arduino CI](https://github.com/RobTillaart/infiniteAverage/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/infiniteAverage/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/infiniteAverage/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/infiniteAverage/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/infiniteAverage/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/infiniteAverage.svg)](https://github.com/RobTillaart/infiniteAverage/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/infiniteAverage/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/infiniteAverage.svg?maxAge=3600)](https://github.com/RobTillaart/infiniteAverage/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/infiniteAverage.svg)](https://registry.platformio.org/libraries/robtillaart/infiniteAverage)


# infiniteAverage

Arduino Library to calculate an average of many samples.


## Description

This library is an experimental library that cascades a float and a uint32_t type.
It was created from an idea when an overflow was encountered in my Statistic Class
due too many samples. https://github.com/RobTillaart/statistic


#### Problem

As an 32 bit float has ~7 decimals precision, after 10 million additions the sum
definitely becomes 7 orders of magnitude larger than individual samples. 
From that moment the addition will not increase the sum correctly or even not at all.
(assume you add values between 0-100 e.g. temperatures)

Taking the average is taking the sum of the samples and divide that by the count.
Only if the count is fixed one could divide the samples first and then sum them.
This library supports the first scenario.


#### Idea 

To cope with the overflow problem, this lib uses an float combined with an uint32_t.

The float is used for the decimal part and the uint32_t for the whole part.
In theory this should give about 15 significant digits for the average in a 9.6 format.
but this precision is only internal to do some math. When the average() is calculated
the value returned is "just" a float.

(since 0.1.2)
If the library detects that there are 4294967000 (almost 2^32) samples added or 
if the internal sum of samples reaches a threshold (default 2^30 ~~ 1 billion) , 
the internal counter and sum are divided by 2. 
That does not affect the minimum and maximum and the average only very slightly.

Since 0.1.4 users can change this threshold and adjust it to data added.
Depending on the data and maxValue per sampel this can have side effects.
Use at your own risk.


#### Conclusion (for now)

The library allows two things
1. take the average of many many samples where normally a summing float would "overflow"
2. take the average of numbers that differ in order of magnitude


#### Notes

**Note** the practical meaning of the average of millions or billions of numbers 
is a discussion worth taking. Normally the outliers are the most interesting. 

**Note** the library is not tested extensively, so use (with care) at your own risk.

**Note** library does not support negative yet. Planned for 0.2.0. 
First get more hands-on experience with it.


## Interface

```cpp
#include "infiniteAverage.h"
```

- **IAVG()** constructor, resets the internal counters to 0
- **void reset()** resets the internal counters to 0
- **void add(float value)** adds value to the internal float uint32_t pair.
- **float decimals()** returns the internal float = decimals part.
- **uint32_t whole()** returns the internal whole part.
- **uint32_t count()** returns the number of values added. 
Note this may be scaled back a power of 2 (2,4,8,16, ...).
- **float average()** returns the average in float format, or NAN if count == 0
- **float minimum()** returns the minimum in float format, or NAN if count == 0
- **float maximum()** returns the maximum in float format, or NAN if count == 0


### 0.1.4

Users can set a threshold value to prevent the internal sum to overflow.
Default at startup this value is (1UL << 30), and depending on the maxValue 
per sample added this should be set lower.
When the threshold is reached both the sum and the internal counter are divided by 2.
This keeps the average almost the same.

The internal sample counter will trigger the divide by 2 action when 4294967000 
samples are added. That is a lot, roughly 1 samples per second for 130 years,
or 1000 samples per second for 40 days.

- **void setDivideThreshold(uint32_t threshold)**
- **uint32_t getDivideThreshold()**


### 0.1.5

- Fixed a rounding error of the whole part when dividing by 2.

The threshold value should be as large as possible to get an accurate value.
If n is small compared to maxValue(sample) there will be side effects that
might break your project. The average will tend to the average of the last
added values. So be careful! 


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

This library has its limits which needs to be investigated.

One could upgrade the idea to a combination of a 8 byte double and a uint64_t
to get around 28 significant digits => 18.10 format 

- investigate "adaptive" scaling, now there is a virtual border at 1, 
  but that could be at **value** (and might be user definable)
  This would allow to adjust to known order of size of the numbers.
  (e.g. if numbers are all in the billions the uint32_t would overflow very fast)
- investigate other math with this data type, starting with + - / \* ?
- printable interface?  sprintf() ?
- play if time permits.
- add examples
- \_overflow => \_wholePart

#### 0.2.0

- add negative numbers
- test negative numbers / mixed numbers.
- move code from .h to .cpp


#### Could

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

