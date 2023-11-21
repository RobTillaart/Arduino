
[![Arduino CI](https://github.com/RobTillaart/RunningMedian/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RunningMedian/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RunningMedian/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RunningMedian/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RunningMedian/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RunningMedian.svg)](https://github.com/RobTillaart/RunningMedian/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningMedian/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningMedian.svg?maxAge=3600)](https://github.com/RobTillaart/RunningMedian/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RunningMedian.svg)](https://registry.platformio.org/libraries/robtillaart/RunningMedian)


# RunningMedian

Arduino library to determine the running median by means of a circular buffer.


## Description

Running Median looks like a running average with a small but important twist.
Running average averages the last N samples while the running median takes 
the last N samples, sort them and take the middle one, or the average of the 
middle two in case the internal buffer size is even.

Important differences between running average and running median:
- Running median will return real data (e.g. a real sample from a sensor) 
if one uses an odd size of the buffer (therefore preferred).
Running average may return a value that is never sampled.
- Running median will give zero weight to outliers, and 100% to the middle sample, 
whereas running average gives the same weight to all samples.
- Running median will give often constant values for some time.
- As one knows the values in the buffer one can predict the maximum change of 
the running median in the next steps in advance.
- Running median is slower as one needs to keep the values in timed order 
to remove the oldest and keep them sorted to be able to select the median.


#### Note: MEDIAN_MAX_SIZE

The maximum size of the internal buffer is defined by **MEDIAN_MAX_SIZE** and is 
set to 255 (since version 0.3.1). The memory allocated currently is in the order
of 5 bytes per element plus some overhead, so 255 elements take ~1300 bytes.
For an UNO this is quite a bit.

With larger sizes the performance penalty to keep the internal array sorted 
is large. For most applications a value much lower e.g. 19 is working well, and 
is performance wise O(100x) faster in sorting than 255 elements.


#### Note: Configurable Options

There are several options that can be configured via defines at compile time, those being:
- **RUNNING_MEDIAN_USE_MALLOC**: bool
  - true (default): Dynamic memory allocation is used for the buffer.
  - false: Static buffers of size MEDIAN_MAX_SIZE are used.
- **MEDIAN_MIN_SIZE**: uint8_t
  - Dynamic / Static: The buffer stores at least this many items.
  - should be minimal 3.
- **MEDIAN_MAX_SIZE**: uint8_t
  - Dynamic: Not used.
  - Static: The buffer stores at most this many items.


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic


## Interface

```cpp
#include "RunningMedian.h"
```


#### Constructor

- **RunningMedian(const uint8_t size)** Constructor, dynamically allocates memory.
- **~RunningMedian()** Destructor.
- **uint8_t getSize()** returns size of internal array.
- **uint8_t getCount()** returns current used elements, getCount() <= getSize().
- **bool isFull()** returns true if the internal buffer is 100% filled.


#### Base functions

- **clear()** resets internal buffer and variables, effectively empty the buffer.
- **add(const float value)** adds a new value to internal buffer, 
optionally replacing the oldest element if the buffer is full.
- **float getMedian()** returns the median == middle element.
- **float getAverage()** returns average of **all** the values in the internal buffer.
- **float getAverage(uint8_t nMedian)** returns average of **the middle n** values. 
This effectively removes noise from the outliers in the samples.
The function is improved in 0.3.8 to correct a bias, see #22.
- **float getMedianAverage(uint8_t nMedian)** almost same as above, 
except it compensates for alignment bias, see #22. 
This is done by adjusting the nMedian parameter (-1 or +1) if needed.
- **float getHighest()** get the largest values in the buffer.
- **float getLowest()** get the smallest value in the buffer.
- **float getQuantile(const float quantile)** returns the Quantile value from the buffer. 
This value is often interpolated.


#### getMedianAverage(nMedian)
 
**getAverage(nMedian)** and **getMedianAverage(uint8_t nMedian)** differ.
When nMedian is odd and count is even or vice versa, the middle N are not 
perfectly in the middle. 
By auto-adjusting nMedian (-1 +1) this balance is restored.

Assume an internal size of 7 elements \[0..6] then 
- **getAverage(4)** will average element 1, 2, 3, 4
- **getMedianAverage(4)** will adjust nMedian and average element 2, 3, 4.

The example **RunningMedian_getMedianAverage.ino** shows the difference.

The implementation of **getMedianAverage(uint8_t nMedian)** is experimental 
and might change in the future. 
Idea is taking top and bottom elements only for 50% if needed, however that 
implies at least 2 extra float multiplications.

It is possible that the name **getMedianAverage(uint8_t nMedian)**
will change in the future to be more descriptive.


#### Less used functions

- **float getElement(const uint8_t n)** returns the n'th element from the values in time order.
- **float getSortedElement(const uint8_t n)** returns the n'th element from the values in size order (sorted ascending).
- **float predict(const uint8_t n)** predict the maximum change of median after n additions, 
n must be smaller than **getSize()/2**.


#### SearchMode optimization

Since 0.3.7 the internal sort has been optimized.
It is now possible to select between LINEAR (=0) and BINARY (=1) insertion sort.
Pre-0.3.7 used linear insertion sort, and the new linear version is slightly optimized.
For larger internal arrays the performance gain of BINARY mode is substantial.

- **void setSearchMode(uint8_t searchMode = 0)** 0 = linear, 1 = binary - see table below.
Other values will set the searchMode to linear.
- **uint8_t getSearchMode()** returns the set mode

|  searchMode  |  value  | notes  |
|:------------:|:-------:|:-------|
|    LINEAR    |    0    |  fastest for smaller internal buffers (default)
|    BINARY    |    1    |  faster for larger internal buffers

Depends on the board / clock used where the methods are equally fast.

Give it a try, and let me know your.


## Operation

See examples.


## Future

#### Must

- improve documentation.

#### Should

#### Could

- check for optimizations.
  - get the median without (full) sorting. QuickSelect()
- move all code to .cpp file


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


