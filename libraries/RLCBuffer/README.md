
[![Arduino CI](https://github.com/RobTillaart/RLCBuffer/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/RLCBuffer/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/RLCBuffer/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/RLCBuffer/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/RLCBuffer/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/RLCBuffer.svg)](https://github.com/RobTillaart/RLCBuffer/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/RLCBuffer/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/RLCBuffer.svg?maxAge=3600)](https://github.com/RobTillaart/RLCBuffer/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/RLCBuffer.svg)](https://registry.platformio.org/libraries/robtillaart/RLCBuffer)


# RLCBuffer

Arduino library for a Run Length Compressed Buffer.


## Description

**Experimental**

This library is to store data in a buffer with Run Length Compression.

The library is a spin of of the LogicAnalyzer library as it needs to store as much
data as possible in limited RAM.

The library works best for measurements that stay stable for longer times.
If the measurements fluctuate a lot, the library is not suitable for the job.

The data elements of the initial version are uint32_t as that matches my needs for now.
In the future the library will be a template class supporting any data type.

This library is strongly related to TLCBuffer, that uses time length compression.

#### Application Measurements

One has to make measurements and those measurements stays stable for long time and
then has some short fluctuations.
Instead of storing many times the same values in the buffer, the library stores how many measurements stays the same.

An example

```
RLCBuffer = { (100, 15), (200, 16), (55, 17), ...
```
The data stream has 100 times the value 15 and then 200 times the value 16, followed by 55 times of value 17 etc.


#### Application IO

One has to monitor several IO lines (e.g. sensors or buttons etc) and there is little
change for long time. One can merge multiple IO lines into a byte / uint32_t and store
that as one data unit. As long as the IO Lines stay the same only the duration is
increased. When a button is pressed the value changes for a short time.

```
RLCBuffer = { (500, 0x0000), (10, 0x0200), (5, 0x0300), (5000, 0x0000), ...
```
very long time no change, then suddenly 10 measurements 1 pin HIGH, 3 measurements 
2 pins HIGH, followed by a long time no activity.


### Notes

The first element of the buffer has default the value 0. Might affect the working.


### Circular Buffer

The first version of the **Run Length Compressed Buffer** is not a circular buffer,
again as I do not need that yet. It might be implemented in the future.

### Related

- https://github.com/RobTillaart/LogicAnalyzer
  - see logicAnalyzer_4_channel_buffer.ino example
- https://github.com/RobTillaart/RLCBuffer uses counter to compress data
- https://github.com/RobTillaart/TLCBuffer uses duration to compress data


### Tested

Tested on Arduino UNO R3.


### Performance

See performance sketch folder.

Note: the performance of begin() depends on the size of the buffer.


## Interface

```cpp
#include "RLCBuffer.h"
```

### Constructor

- **RLCBuffer(uint32_t size)** create a buffer of size elements (uint32_t).
- **~RLCBuffer()** destructor, frees allocated memory.
- **bool begin()** returns true if allocation succeeded.
Only if succeeded the function resets the internal variables.

Note that the RAM used by the buffer is 2 uint32_t (8 bytes) per element,
one for the counter, and one for the value. 
One could change the counter to an uint16_t to save some RAM.


### Meta

- **uint32_t size()** return size set in constructor.
- **uint32_t count()** return internal counter of elements used.
- **uint32_t index()** return internal index.
- **bool empty()** returns true if buffer has no elements.
- **bool full()** returns true if buffer has no space left.
- **uint32_t available()** returns number of available free slots.

### Read Write

- **void writeData(uint32_t value)** add an element to buffer.
- **uint32_t readData(uint32_t index)** read an element.
- **uint32_t readDuration(uint32_t index)** read the duration of an element.

**writeData()** will increase the duration if the value equals the previous one. Otherwise it uses a new entry.

### Error


## Future

#### Must

- improve documentation
- test functionality
- keep in sync with TLCBuffer.

#### Should

- add examples.
- investigate template version,
  - first get one simple version working.
- implement circular behaviour
  - first get base buffer right (derived class circular?)
  - readValue() reads oldest.
  - need head / tail index.
- implement error handling (?)

#### Could

- add unit tests

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


