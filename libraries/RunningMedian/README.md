
[![Arduino CI](https://github.com/RobTillaart/RunningMedian/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningMedian/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningMedian.svg?maxAge=3600)](https://github.com/RobTillaart/RunningMedian/releases)


# RunningMedian

Arduino library to determine the running median by means of a circular buffer.


## Description

Running Median looks like a running average with a small but important twist.
Running average averages the last N samples while the running median takes 
the last N samples, sort them and take the middle one, or the average of the 
middle two in case the internal buffer size is even.

Important differences between running average and running median:
- Running median will return real data (e.g. a real sample from a sensor) 
if one uses an odd size of the buffer (therefor preferred).
Running average may return a value that is never sampled.
- Running median will give zero weight to outliers, and 100% to the middle sample, 
whereas running average gives the same weight to all samples.
- Running median will give often constant values for some time.
- As one knows the values in the buffer one can predict the maximum change of 
the running median in the next steps in advance.
- Running median is slower as one needs to keep the values in timed order 
to remove the oldest and keep them sorted to be able to select the median.


#### Note MEDIAN_MAX_SIZE

The maximum size of the internal buffer is defined by **MEDIAN_MAX_SIZE** and is 
set to 255 (since version 0.3.1). The memory allocated currently is in the order
of 5 bytes per element plus some overhead, so 255 elements take ~1300 bytes.
For an UNO this is quite a bit.

With larger sizes the performance penalty to keep the internal array sorted 
is large. For most applications a value much lower e.g. 19 is working well, and 
is performance wise O(100x) faster in sorting than 255 elements.


## Interface


### Constructor

- **RunningMedian(const uint8_t size)** Constructor, dynamically allocates memory.
- **~RunningMedian()** Destructor
- **uint8_t getSize()** returns size of internal array
- **uint8_t getCount()** returns current used elements, getCount() <= getSize()
- **bool isFull()** returns true if the internal buffer is 100% filled.


### Base functions

- **clear()** resets internal buffer and variables, effectively emptird thr buffer.
- **add(const float value) ** adds a new value to internal buffer, optionally replacing the oldest element if the buffer is full
- **float getMedian()** returns the median == middle element
- **float getAverage()** returns average of **all** the values in the internal buffer
- **float getAverage(uint8_t nMedian)** returns average of **the middle n** values. 
This effectively removes noise from the outliers in the samples.
- **float getHighest()** get the largest values in the buffer.
- **float getLowest()** get the smallest value in the buffer.
- **float getQuantile(const float q)** returns the Quantile value from the buffer. 
This value is often interpolated.


### Less used functions

- **float getElement(const uint8_t n)** returns the n'th element from the values in time order.
- **float getSortedElement(const uint8_t n)** returns the n'th element from the values in size order (sorted ascending)
- **float predict(const uint8_t n)** predict the max change of median after n additions, n should be smaller than **getSize()/2**


## Operation

See examples
