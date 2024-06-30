
[![Arduino CI](https://github.com/RobTillaart/RunAvgWeight/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RunAvgWeight/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RunAvgWeight/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RunAvgWeight/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RunAvgWeight/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RunAvgWeight.svg)](https://github.com/RobTillaart/RunAvgWeight/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunAvgWeight/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunAvgWeight.svg?maxAge=3600)](https://github.com/RobTillaart/RunAvgWeight/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RunAvgWeight.svg)](https://registry.platformio.org/libraries/robtillaart/RunAvgWeight)


# RunAvgWeight

Arduino library to calculate the running average with weights by means of a circular buffer.


## Description

**Experimental**

The RunAvgWeight (RAW) object gives a running average of the last N floating point numbers, 
while giving them a different weight.

This is done by adding new data to internal circular buffers, removing the oldest and 
replace it by the newest. 
The size of the internal buffer can be set in the constructor.

The interface of the RunAvgWeight object is strongly based upon **RunningAverage**.
However not all functions are implemented.

**Warning**

However the constant adding and subtracting when adding new elements to the RAW object 
possibly introduces an ever increasing error. 
In tests with **RunningAverage** class with equal weights, adding up to 1500000 numbers 
this error was always small. Be aware of this.


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunAvgWeight
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/printHelpers - print scientific format
- https://github.com/RobTillaart/Statistic


## Interface

```cpp
#include "RunAvgWeight.h"
```

### Constructor

- **RunAvgWeight(uint16_t size)** allocates dynamic memory, one float (4 bytes) per element. 
No default size (yet).
- **~RunAvgWeight()** destructor to free the memory allocated.


### Basic

- **void clear()** empties the internal buffers.
- **void addValue(float value, float weight)** adds a new value to the object, 
if the internal buffer is full, the oldest element is removed.
- **float getValue(uint16_t position)** returns the value at **position** from the additions. 
Position 0 is the first one to disappear.
- **float getAverage()** iterates over all elements to get the average, slower but accurate. 
Updates the variables used by **getFastAverage()** to improve its accuracy again.
- **float getFastAverage()** reuses previous calculated values, therefore faster. Accuracy can drift.


### Extended functions

- **float getStandardDeviation()** returns the standard deviation of the current content. 
Needs more than one element to be calculable.
- **float getStandardError()** returns the standard error of the current content.
- **float getMin()** returns minimum since last clear, does not need to be in the buffer any more.
- **float getMax()** returns maximum since last clear, does not need to be in the buffer any more.
- **float getMinInBuffer()** returns minimum in the internal buffer.
- **float getMaxInBuffer()** returns maximum in the internal buffer.


### Admin functions

- **bool bufferIsFull()** returns true if buffer is full.
- **float getElement(uint16_t index)** get element directly from internal buffer at index. (debug)
- **uint16_t getSize()** returns the size of the internal array.
- **uint16_t getCount()** returns the number of slots used of the internal array.



## Future

#### Must

- update documentation
- keep in sync with RunningAverage

#### Should

- elaborate unit test

#### Could

#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


