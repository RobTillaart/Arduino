
[![Arduino CI](https://github.com/RobTillaart/RunningAverage/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RunningAverage/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RunningAverage/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RunningAverage/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RunningAverage/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RunningAverage.svg)](https://github.com/RobTillaart/RunningAverage/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningAverage/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningAverage.svg?maxAge=3600)](https://github.com/RobTillaart/RunningAverage/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RunningAverage.svg)](https://registry.platformio.org/libraries/robtillaart/RunningAverage)


# RunningAverage

Arduino library to calculate the running average by means of a circular buffer.


## Description

The RunningAverage object gives a running average of the last N floating point numbers, 
giving them all equal weight.
This is done by adding new data to an internal circular buffer, removing the oldest and 
replace it by the newest. 
The size of the internal buffer can be set in the constructor.

By keeping track of the **\_sum** the runningAverage can be calculated fast (only 1 division)
at any time. This is done with **getFastAverage()**. 
However the constant adding and subtracting when adding new elements to the RA object possibly 
introduces an ever increasing error. 
In tests adding up to 1500000 numbers this error was always small. But that is no proof.
In version 0.2.16 a fix was added that uses the calculation of the sum in **getAverage()** to 
update the internal **\_sum**.


#### Related

- https://github.com/RobTillaart/Correlation
- https://github.com/RobTillaart/GST - Golden standard test metrics
- https://github.com/RobTillaart/Histogram
- https://github.com/RobTillaart/RunningAngle
- https://github.com/RobTillaart/RunningAverage
- https://github.com/RobTillaart/RunningMedian
- https://github.com/RobTillaart/statHelpers - combinations & permutations
- https://github.com/RobTillaart/Statistic
- https://github.com/RobTillaart/Student


## Interface

```cpp
#include "RunningAverage.h"
```

### Constructor

- **RunningAverage(uint16_t size)** allocates dynamic memory, one float (4 bytes) per element. 
No default size (yet).
- **~RunningAverage()** destructor to free the memory allocated.


### Basic

The following functions return **false** if the internal buffer is not allocated.

- **bool clear()** empties the internal buffer.
- **bool add(float value)** wrapper for **addValue()**.
- **bool addValue(float value)** adds a new value to the object, if the internal buffer is full, 
the oldest element is removed.
- **bool fillValue(float value, uint16_t number)**  adds number elements of value. 
Good for initializing the system to a certain starting average.


The following functions returns NAN if there are no values present (count == 0) or 
of internal array is not allocated.

- **float getValue(uint16_t position)** returns the value at **position** from the additions. 
Position 0 is the first one to disappear.
- **float getAverage()** iterates over all elements to get the average, slower but accurate. 
Updates the variables used by **getFastAverage()** to improve its accuracy again.
- **float getFastAverage()** reuses previous calculated values, therefore faster. Accuracy can drift.


### Extended functions

- **float getStandardDeviation()** returns the standard deviation of the current content. 
Needs more than one element to be calculable.
- **float getStandardError()** returns the standard error of the current content.
- **float getCoefficientOfVariation()** returns coefficient of variation.
This is defined as standardDeviation / Average. 
It indicates if the distribution is relative small ( < 1) or relative wide ( > 1).
Note it has no meaning when the average is zero (or close to zero).
- **float getMin()** returns minimum since last call to clear(). 
The returned value does not need to be in the buffer any more.
- **float getMax()** returns maximum since last call to clear(). 
The returned value does not need to be in the buffer any more.
- **float getMinInBuffer()** returns minimum in the internal buffer.
- **float getMaxInBuffer()** returns maximum in the internal buffer.
- **float getSum()** returns sum of values in the internal buffer.


### Admin functions

- **bool bufferIsFull()** returns true if buffer is full.
- **float getElement(uint16_t index)** get element directly from internal buffer at index. (debug)
- **uint16_t getSize()** returns the size of the internal array as set in constructor.
- **uint16_t getCount()** returns the number of slots used of the internal array.


## Partial functions

- **bool setPartial(uint16_t partial = 0)** use only a part of the internal array. 
Allows to change the weight and history factor. 
0 ==> use all == default.
Returns false if internal buffer is not allocated.
- **uint16_t getPartial()** returns the set value for partial.


## Last functions

These functions get the basic statistics of the last N added elements. 
Returns NAN if there are no elements and it will reduce count if there are less than 
count elements in the buffer.

- **float getAverageLast(uint16_t count)** get the average of the last count elements.
- **float getStandardDeviationLast(uint16_t count)** get the stddev of the last count elements.
- **float getMinInBufferLast(uint16_t count)** get the minimum of the last count elements.
- **float getMaxInBufferLast(uint16_t count)** get the maximum of the last count elements.

These functions are useful in cases where you might want to calculate and display the 
statistics of a subset of the added elements. Reason might be to compare this with the 
numbers of the whole buffer to notice changes earlier. 
Otherwise one should create multiple RunningAverage objects each with its own length, 
effectively having multiple copies of the data added. 

Note: if called with a value larger or equal to **getCount()**  (including **getSize()**) as 
parameter, the functions will return the statistics of the whole buffer. 


## Subset (experimental)

- **float getAverageSubset(uint16_t start, uint16_t count)** 
Get the average of subset - count elements from start.
Returns NAN if no elements or internal array not allocated.


## Performance

Indicative performance on an UNO, see examples.

|  Function              |  0.4.5 us  |  0.4.6 us  |  Notes  |
|:----------------------:|:----------:|:----------:|:-------:|
|  clear                 |      60    |      60    |
|  addValue              |      24    |      24    |
|  fillValue             |    1512    |    1520    |
|  getValue              |       4    |       8    |
|  getAverage            |     520    |     552    |
|  getFastAverage        |      36    |      40    |
|  getStandardDeviation  |    1856    |    1856    |
|  getStandardError      |    1920    |    1920    |
|  getMin                |       8    |       4    |
|  getMax                |       4    |       4    |
|  getMinInBuffer        |     216    |     212    |
|  getMaxInBuffer        |     208    |     208    |
|  getSum                |       -    |       8    |
|  bufferIsFull          |       8    |       8    |
|  getElement            |       4    |       4    |
|  getSize               |       8    |       8    |
|  getCount              |       8    |       8    |
|  last functions        |       -    |       -    |  not tested


## Operation

See examples


## Future

#### Must

- update documentation, explain better

#### Should

- check for optimizations.
  - divide by count (-1) happens often.
  - fillValue can be optimized (See #13).

#### Could

- create a double based derived class? 
  - Template class?
- add error handling (important?).

#### Wont

- default size for constructor
  - unknown what would be a good choice.
- clear(bool zero = true) to suppress setting all to 0. ?
  - makes **addValue()** slightly more complex
  - could introduce conflicts due to randomness data?
- investigate **modus()** most frequently occurring value.
  - difficult with floats ?
  - what to do when on two or more values are on par? (no modus?)
- **int getUniqueValuesInBuffer()** O(n^2).


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


