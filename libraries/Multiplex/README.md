
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

Multiplex is a library in which one can add multiple **Print** streams to a multiplexer.
If one prints to the multiplexer the data is sent to all the streams that were added and enabled.

Streams can be enabled or disabled by calling `enable()/disable()` passing either an index 
(based on the order in which `add()` was called; 0 is first) 
or a pointer to the `Print` object that was passed to `add(Print *)` by calling `enableStream()/disableStream()`
Default all streams are enabled.

Typical application is to multiplex the output of Serial to an SD card.

Note: the different streams will get the data in order of their addition,
and therefore they will get the data at (slightly) different times.

Feedback as always is welcome.


### Number of streams

The maximum number of streams to add is default 4. 
This value is defined in the **multiplex.h file** and can be overruled on the command line. 

```cpp
#define MAX_MULTIPLEX  4
```

This value can be set to 254 MAX as the number 255 / 0xFF is used as a NOT_FOUND flag.
Setting MAX_MULTIPLEX to zero creates a sort of /dev/null as it will has no output.
Setting MAX_MULTIPLEX to one creates a single stream that one can enable/disable.


### Removal of streams

Since 0.2.2 the library has **experimental** remove support.

Current implementation (0.2.8) keeps the remaining streams in the same order, 
however some streams will have a new index.
So the order in which streams are handled will stay the same.
The associated indices of the streams might / will change so removing might have side effects.

There are some ways to prevent / handle this effect:
- use **reset()** and repopulate the multiplexer. 
- disable the stream instead of removing. As long as there is room for new streams this might be preferred.
- call **index(Stream)** to verify / update the indices used.
- do not use the index based functions. 

To remove all streams just call **reset()**

Feedback as always is welcome.


### Related

- https://github.com/RobTillaart/LineFormatter
- https://github.com/RobTillaart/XMLWriter


## Interface

```cpp
#include "Multiplex.h"
```

### Constructor

- **Multiplex()** constructor, 
sets the maximum number of streams to MAX_MULTIPLEX == 4 by default. 
MAX number is 254 as 255 (0xFF) is used as a flag for **NOT FOUND**.
- **~Multiplex()** destructor.

### Populate

- **void reset()** resets the count in the multiplexer to zero streams.
Effectively a remove all.
- **bool add(Print \* stream)** add another Print stream. 
Returns true on success. 
Returns false if no space left, or when stream already in multiplex.
Use the **index(Stream)** to get the actual index of the stream.
- **bool remove(Print \* stream)** remove a Print stream. 
Returns false if the stream is not in the multiplexer.
- **bool remove(uint8_t index)** remove a stream by its internal index.
Returns false if index is out of range.

Removing a stream changes the internal indices used. See removal of streams section above.

### Find

- **uint8_t index(Print \*stream)** returns the index of the stream if it was added,
otherwise it returns 0xFF == 255.  
Can be used to check if a stream is added to the multiplexer.
- **Print \* stream(uint8_t index)** returns the stream at index or NULL otherwise.
Convenience function.

### Metrics 

- **uint8_t count()** returns number of streams added, MAX 4 in initial release
- **uint8_t size()** returns size which is 4 in the current release.
- **uint8_t free()** returns number of free slots, 0 .. 4.

### Core

- **size_t write(uint8_t c)** workhorse of the Print interface. 
Writes a character to all enabled streams.
- **size_t write(const uint8_t \* buffer, size_t size)** 
Writes a buffer of size characters to all enabled streams.
- **virtual void flush() override** flushes all enabled streams.

With respect to the two **write()** functions:

The multiplexing performance will be affected by the number of streams and their behaviour. 
A slow stream can "block" the performance of streams added later.
Networks streams might block due to non availability of a destination. 
A file on SD card might block due to a full SD card, or corrupt file.

### Enable / disable

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

### Diagnostic

(since 0.2.4)

The output count function was added for diagnostic tests. 
It is kept in the library for now, however it might be removed in the future.
Footprint is minimal.

- **uint32_t getOutputCount()** returns number of bytes multiplexed.
So if 6 bytes are sent to 3 streams the output byte count is 3 x 6 = 18.
For diagnostic purpose.
- **void resetOutputCount()** set internal counter to 0.


## Future

#### Must

- improve documentation

#### Should

- should **int add()** return the index? Or -1 if fails.
  - usable idea
  - breaking change  ==> 0.3.0

#### Could

- error handling
  - add an error flag if one of the streams does not **write()**
correctly and returns 0 or less than it should.
- add examples
- add performance measurement - KB / second (needs investigation)
  - user need to test / measure its own configuration
- set multiplex per char or per buffer (needs investigation)

#### Wont

- set size in constructor 
  - dynamic memory for all internal arrays (footprint increase)
- pack enabled flag in one or more bytes. 
  (not much faster + need to encode/decode)
- add names?
  (too much memory)
- test to prevent circular addition of streams?
  - no, is risk of the user.
- add **removeAll()** ==> reset() works.
- move all code to .cpp

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

