
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

The RunAvgWeight object gives a running average of the last N floating point numbers, 
while giving them a different weight.

This is done by adding the new data to the internal circular buffers, removing the oldest 
and replace them by the newest. 
The size of the internal buffers must be set in the constructor.

The interface of the RunAvgWeight object is strongly based upon **RunningAverage**.
However not all functions are implemented.
Note the **RunningAverage** library uses no weights.

**Warning**

However the constant adding and subtracting when adding new elements to the RAW object 
possibly introduces an ever increasing error. 
In tests with **RunningAverage** library (with equal weights), adding up to 1500000 numbers 
this error was always small. Still you need to be aware of this limit.

### 0.2.0 breaking change

Fixed #6 by fixing **clear()**, previous versions are now obsolete.


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
- https://github.com/RobTillaart/Student


## Interface

```cpp
#include "RunAvgWeight.h"
```

### Constructor

- **RunAvgWeight(uint16_t size)** allocates dynamic memory, two floats (8 bytes) per element. 
The object has no default size.
- **~RunAvgWeight()** destructor to free the memory allocated.


### Basic

- **bool clear()** empties the internal buffers.
- **bool addValue(float value, float weight = 1.0)** adds a new value to the object, 
if the internal buffer is full, the oldest element is removed.
The default weight is 1.0 so one can use this class as a "unweighted" running average too,
albeit with the extra overhead.  
**addValue()** updates the sum of values and weights for the **getFastAverage()** function.


The following functions returns NAN if there are no values present (count == 0) or 
of internal array is not allocated.

- **float getValue(uint16_t position)** returns the value at **position** from the additions. 
Position 0 is the first one to disappear.
- **float getWeight(uint16_t position)** returns the weight at **position** from the additions. 
Position 0 is the first one to disappear.
- **float getAverage()** iterates over all elements, values and weights, to get the average.
This is the slower and the more accurate method. 
A call to **getAverage()** updates the internal variables used by **getFastAverage()** to 
improve its accuracy again.
- **float getFastAverage()** reuses previous calculated values, therefore faster. Accuracy can drift.


### Extended functions

- **float getStandardDeviation()** returns the standard deviation of the current content. 
More than one element needs to be added to be calculable.
- **float getStandardError()** returns the standard error of the current content.
- **float getCoefficientOfVariation()** returns coefficient of variation.
This is defined as standardDeviation / Average. 
It indicates if the distribution is relative small ( < 1) or relative wide ( > 1).
Note it has no meaning when the average is zero (or close to zero).
- **float getMin()** returns minimum value since last **clear()**. This value does not need 
to be in the internal buffer any more. Useful for graphing long term minima.
Note the returned minimum is **unweighted.**
- **float getMax()** returns maximum value since last **clear()**. This value does not need 
to be in the internal buffer any more. Useful for graphing long term maxima.
Note the returned maximum is **unweighted.**
- **float getMinInBuffer()** returns minimum value in the internal buffer.
Note the returned minimum is **unweighted.**
- **float getMaxInBuffer()** returns maximum value in the internal buffer.
Note the returned maximum is **unweighted.**


### Admin functions

- **bool bufferIsFull()** returns true if buffer is full.
- **uint16_t getSize()** returns the size of the internal array.
- **uint16_t getCount()** returns the number of slots used of the internal array.


### Helper functions

- **float getElementValue(uint16_t index)** get element directly from internal buffer at index.
- **float getElementValue(uint16_t index)** get element directly from internal buffer at index.
- **float getSumValues()** returns the sum of the values \* weights in the internal buffer.
- **float getSumWeights()** returns the sum of the values in the internal buffer.


## Future

#### Must

- update documentation
- keep in sync with RunningAverage

#### Should

- elaborate unit test

#### Could

- implement missing RunningAverage functions?

#### Wont

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


