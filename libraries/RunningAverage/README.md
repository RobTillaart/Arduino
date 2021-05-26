
[![Arduino CI](https://github.com/RobTillaart/RunningAverage/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RunningAverage/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RunningAverage.svg?maxAge=3600)](https://github.com/RobTillaart/RunningAverage/releases)

# RunningAverage

Arduino library to calculate the running average by means of a circular buffer.


## Description
The RunningAverage object gives a running average of the last N numbers, giving them
all equal weight. This is done by adding new data to an internal circular buffer, 
removing the oldest and replace it by the newest. The size of the internal buffer 
can be set in the constructor.

By keeping track of the **\_sum** the runningAverage can be calculated fast (only 1 division).
This is done with **getFastAverage()**. 
However the constant adding/subtracting when adding new elements introduces an accumulating error. 
In tests adding up to 1500000 numbers this error was always small. But that is no proof.
In version 0.2.16 there is a fix added that uses the calculation of the sum in **getAverage()** to 
update the internal **\_sum**.


## Interface

### Constructor

- **RunningAverage(size)** allocates dynamic memory, one float (4 bytes) per element. 
No default size (yet).
- **~RunningAverage()** deconstructor to free the memory allocated.


### Basic

- **clear()** empties internal buffer.
- **add(value)** wrapper for **addValue()**
- **addValue(value)** adds a new value to the object, if internal buffer is full, the oldest element is removed.
- **fillValue(value, nr)**  adds nr elements of value. Good for initializing system.
- **getValue(pos)** returns element at position **pos**.
- **getAverage()** iterates over all elements to get the average, slower but accurate
- **getFastAverage()** reuses previous calculated values, therefor faster. Accuracy can drift.


### Extended functions

- **getStandardDeviation()** returns the stddev of the current content. Needs more than one element.
- **getStandardError()** returns the stderror of the current content.
- **getMin()** returns minimum since last clear, does not need to be in the buffer.
- **getMax()** returns maximum since last clear, does not need to be in the buffer.
- **getMinInBuffer()** returns minimum in the internal buffer.
- **getMaxInBuffer()** returns maxumum in the internal buffer.


### Admin functions

- **bufferIsFull()** returns true if buffer is full.
- **getElement(idx)** get element directly from internal buffer. (debug)
- **getSize()** idem.
- **getCount()** idem.


## Operation

See examples
