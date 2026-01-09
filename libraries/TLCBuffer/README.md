
[![Arduino CI](https://github.com/RobTillaart/TLCBuffer/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TLCBuffer/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TLCBuffer/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TLCBuffer/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TLCBuffer/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TLCBuffer.svg)](https://github.com/RobTillaart/TLCBuffer/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TLCBuffer/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TLCBuffer.svg?maxAge=3600)](https://github.com/RobTillaart/TLCBuffer/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TLCBuffer.svg)](https://registry.platformio.org/libraries/robtillaart/TLCBuffer)


# TLCBuffer

Arduino library for a Time Length Compressed Buffer.


## Description

**Experimental**

This library is to store data in a buffer with **Time Length Compression**.

The library is a spin of of the LogicAnalyzer library as it needs to store as much
data as possible in limited RAM.

The library works best for series of measurements that stay stable for longer times.
If the measurements fluctuate a lot, the library is not suitable for the job.

The data elements of the 0.1.0 version are uint32_t as that matches my needs.
In the 0.2.0 version it became a template class so other types (e.g. int16) 
could be stored efficiently. (for now numeric only).

This library is strongly related to RLCBuffer, that uses Run Length Compression.

FEedback as always is welcome.


#### Application: Measurements

One has to make measurements and those measurements stays stable for long time and
then has some short fluctuations.
Instead of storing many times the same values in the buffer, the library stores how long
(= duration) the data (= measurement) stays the same.

An example

```
TLCBuffer = { (10000, 15), (200, 16), (550, 17), ...
```
The data stays 10000 milliseconds the value 15 and then for 200 milliseconds the
value 16, followed by 550 milliseconds of value 17 etc.

#### Application: IO

One has to monitor several IO lines (e.g. sensors or buttons etc.) and there is little
change for long time. One can merge multiple IO lines into a byte / uint32_t and store
that as one data unit. As long as the IO Lines stay the same only the duration is
updated. When a button is pressed the (combined) value changes for a short time.

```
TLCBuffer = { (10000000, 0x0000), (152, 0x0200), (500000, 0x0000), ...
```
very long time no change, then suddenly a short time 1 pin HIGH followed by a long time
no activity.

This way one could e.g. store button presses and replay them.

#### Application: keys

The TLCBuffer could be used to store a piano (midi) key and its duration.

Another application is recording a (ASCII) keyboard to see the duration between the
different keys.

### Notes

The first element of the buffer has default the value 0. Might affect the working.

Instead of the duration it is also possible to add the time-stamp of when the time
changed. However that means for the duration one has to know the next change / element.
Might be a breaking change in the future.s

### Circular Buffer: experimental 0.2.0

The first version of the **Time Length Compressed Buffer** did not have a circular buffer.
In version 0.2.0 the circular buffer is implemented but needs more rigorous testing.
This means when the buffer is full, oldest data will be overwritten.


### Related

- https://github.com/RobTillaart/LogicAnalyzer
  - see logicAnalyzer_4_channel_buffer.ino example.
- https://github.com/RobTillaart/RLCBuffer uses counter to compress data.
- https://github.com/RobTillaart/TLCBuffer uses duration to compress data.


### Tested

Tested on Arduino UNO R3.


### Performance

See performance sketch folder.

Note: the performance of begin() depends on the size of the buffer.


## Interface

```cpp
#include "TLCBuffer.h"
```

### Constructor

- **TLCBuffer<typename T_DATA = uint32_t, typename T_TIME = uint32_t> TLCB(uint32_t size)** 
Allocates a buffer of size elements (uint32_t), the minimum created will be 4 elements. 
To reduce the memory footprint per element, one can change the T_DATA and T_TIME to 
smaller data types.
T_TIME must be an integer type (uint32_t..uint8_t) as it holds timestamps.
- **~TLCBuffer()** destructor, frees the allocated memory.
- **bool begin(char timeUnits = 'm')** returns true if allocation succeeded.
Only if succeeded the function resets the internal variables.
Finally it sets the time units (see below), where invalid values are handled as millis().

|  unit  |  unit  |  description  |
|:------:|:------:|:--------------|
|    u   |  1e-6  |  microseconds
|    m   |  1e-3  |  milliseconds  (default)
|    h   |  0.01  |  hundreds of a second
|    t   |  0.10  |  tenths of a second
|    s   |  1.00  |  seconds
| other  |  1e-3  |  milliseconds (fall back)

Note that the RAM used by the buffer is default two uint32_t (8 bytes) per element,
one for the duration, and one for the value. 
The template class allows to reduce that e.g. the following used only 2 bytes per element.

```cpp
TLCBuffer<uint8_t, uint8_t> TLCB(20);  //  minimize RAM usage
```


### Meta

- **uint32_t size()** return size set in constructor.
- **uint32_t count()** return internal counter of elements used.
- **uint32_t index()** return internal index.
- **bool empty()** returns true if buffer has no elements.
- **bool full()** returns true if buffer has no space left.
- **uint32_t available()** returns number of available free slots.

### Read Write

- **void writeData(T_DATA value)** add an T_DATA element to buffer.
It will update the duration if the value equals the previous one. 
Otherwise it uses the next entry of the buffer.
- **T_DATA readData(uint32_t index)** read an T_DATA element.
- **T_TIME readDuration(uint32_t index)** read the T_TIME duration of an element.

Note: since 0.2.0 the internal buffer is circular so old data might be overwritten.
Also the **readData(), readDuraton()** reduces the index to fit within 0..size-1.


### Error

- **char getTimeUnit()** returns time unit for convenience. 
See table above.


## Future

#### Must

- improve documentation
- test functionality
- keep in sync with RLCBuffer.

#### Should

- add examples.
  - XML?

#### Could

- implement circular behaviour
  - first get base buffer right (derived class circular?)
  - readValue() reads oldest.
  - need head / tail index.
- make timeUnits an enum
- add unit tests
- implement error handling (?)
- investigate serializing (?)

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


