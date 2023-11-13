
[![Arduino CI](https://github.com/RobTillaart/Multiplex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Multiplex/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Multiplex/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Multiplex/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Multiplex/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Multiplex.svg)](https://github.com/RobTillaart/Multiplex/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Multiplex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Multiplex.svg?maxAge=3600)](https://github.com/RobTillaart/Multiplex/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Multiplex.svg)](https://registry.platformio.org/libraries/robtillaart/Multiplex)


# Multiplex

Arduino Library implementing a (Print) stream multiplexer.


## Description

Multiplex is a library in which one can add multiple Print streams.
If one prints to the multiplexer the data is sent to all the streams that were added and are enabled.

Streams can be enabled or disabled by calling `enable()/disable()` passing either an index (based on the order 
in which `add()` was called; 0 is first) or a pointer to the `Print` 
object that was passed to `add(Print *)` by calling `enableStream()/disableStream()`
Default all streams are enabled.



### Number of streams

The maximum number of streams to add is default 4. 
This value is defined in the **multiplex.h file** and can be overruled on the command line. 

```cpp
#define MAX_MULTIPLEX  4
```

This value can be set to 254 MAX as the number 255 / 0xFF is used as a NOT_FOUND flag.


### Removal of streams

Since 0.2.2 the library has **experimental** remove support.

The effect of the current implementation of removal is that the order in which the streams are handled
can change as the indices are affected. 
If you want to prevent this effect, you should use **reset()** and repopulate the multiplexer.


## Interface

```cpp
#include "Multiplex.h"
```

### Constructor

- **Multiplex()** constructor, 
sets the maximum number of streams to MAX_MULTIPLEX == 4 by default. 
MAX number is 254 as 255 (0xFF) is used as a flag for **NOT FOUND**.
- **~Multiplex()** destructor
- **void reset()** resets the count in the multiplexer to zero streams.
Effectively a remove all.


### Core

- **bool add(Print \* stream)** add another Print stream. 
Returns true on success. 
Returns false if no space left, or when stream already in multiplex.
Use the **index(Stream)** to get the actual index of the stream.
- **size_t write(uint8_t c)** workhorse of the Print interface. 
Writes a character to all enabled streams.
- **size_t write(const uint8_t \* buffer, size_t size)** 
Writes a buffer of size characters to all enabled streams.
- **virtual void flush() override** flushes all enabled streams.

With respect to the two **write()** functions:

The performance will be affected by the number of streams and their performance. 
One slow stream can hold them all.
Note: the different streams will get the data in order of addition,
and therefore they will get the data at different times.


### Remove - experimental

(since 0.2.2)

Removing a stream is still experimental. Feedback is welcome.
Removing a stream changes the internal indices used. 
So if you want to use **remove()** in your sketch,
only use the functions with a stream as parameter as these will always work correctly.  
Alternative is to request the **uint8_t index(Stream)** after you called 
**remove()** and update your own used indices. 

- **bool remove(Print \* stream)** remove a Print stream. 
Returns false if the stream is not in the multiplexer.
- **bool remove(uint8_t index)** remove a stream by its internal index.
Returns false if index is out of range.


### Control

#### Info 

- **uint8_t count()** returns number of streams added, MAX 4 in initial release
- **uint8_t size()** returns size which is 4 in the current release.
- **uint8_t free()** returns number of free slots, 0 .. 4.


#### enable / disable

Note: the index based functions are (slightly) faster than the stream based functions.  
How much faster depends on **MAX_MULTIPLEX** as the stream based functions do a lookup in every call. 
- **bool enable(uint8_t index)** enable the stream at index.
Returns true on success, false otherwise.
- **bool enableStream(Stream \* stream)** enable the stream.
Returns true on success, false otherwise.
- **bool disable(uint8_t index)** disable the stream at index.
Returns true on success, false otherwise.
- **bool disableStream(Stream \* stream)** disable the stream.
Returns true on success, false otherwise.
- **bool isEnabled(uint8_t index)** returns true if the stream at index is enabled,
false otherwise.
- **bool isEnabledStream(Stream \* stream)** returns true if the stream is enabled,
false otherwise.
- **bool isEnabledAny()** returns true if at least one stream is enabled. 
If false is returned it makes no sense to print anything.


#### Lookup functions

- **uint8_t index(Print \*stream)** returns the index of the stream if it was added,
otherwise it returns 0xFF == 255.  
Can be used to check if a stream is added to the multiplexer.
- **Print \* stream(uint8_t index)** returns the stream at index or NULL otherwise.
Convenience function.


### OutputCount - experimental

(since 0.2.4)

The output count function was added for diagnostic tests. 
It is kept in the library for now, however it might be removed in the future.
Footprint is minimal.

- **uint32_t getOutputCount()** returns number of bytes multiplexed.
So if 6 bytes are sent to 3 streams the output byte count is 3 x 6 = 18.
For diagnostic purpose.
- **void resetOutputCount()** set internal counter to 0.


## Operation

See examples


## Future

#### Must

- improve documentation

#### Should

- set size in constructor 
  - dynamic memory for all internal arrays
  - breaking change  ==> 0.3.0
- should **int add()** return the index? Or -1 if fails.
  - usable idea
  - breaking change  ==> 0.3.0
- add **removeAll()** ==> reset()

#### Could

- error handling
  - add an error flag if one of the streams does not **write()**
correctly and returns 0 or less than it should.
- add more examples.
- add performance measurement
  - KB / second
- move all code to .cpp

#### Wont

- pack enabled flag in one or more bytes. 
  (not much faster + need to encode/decode)
- add names?
  (too much memory)
- test to prevent circular addition of streams?
  - no, is risk of the user.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

