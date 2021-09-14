
[![Arduino CI](https://github.com/RobTillaart/Multiplex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![JSON check](https://github.com/RobTillaart/Multiplex/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Multiplex/actions/workflows/jsoncheck.yml)
[![Arduino-lint](https://github.com/RobTillaart/Multiplex/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Multiplex/actions/workflows/arduino-lint.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Multiplex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Multiplex.svg?maxAge=3600)](https://github.com/RobTillaart/Multiplex/releases)

# Multiplex

Arduino Library implementing a (Print) stream multiplexer.


## Description

Multiplex is a library in which one can add multiple Print streams.
If one prints to the multiplexer the data is sent to all the streams that were added.

The maximum number of streams to add is 4. This value is defined in the **multiplex.h file** with `#define MAX_MULTIPLEX`
This value can be set to 254 MAX as the number 255 / 0xFF is used as a NOT_FOUND flag.

Streams can be enabled or disabled by calling `enable()/disable()` passing either an index (based on the order 
in which `add` was called; 0 is first) or a pointer to the `Print` 
object that was passed to `add(Print *)` by calling `enableStream()/disableStream()`

It is not possible to remove a stream from the multiplexer (yet), as this would affect the indices used.
Solution is to reset and repopulate for now.


## Interface


### Constructor

- **Multiplex(uint8_t max_multiplex = 4)** constructor, 
sets the maximum number of streams to 4 by default. 
MAX number is 254 as 255 (0xFF) is used as a flag for **NOT FOUND**.
- **~Multiplex()** destructor
- **void reset()** resets the count in the multiplexer to zero streams.


### Core

- **size_t write(uint8_t c)** workhorse of the print interface. 
Writes a character to all enabled streams.
- **size_t write(const uint8_t \*buffer, size_t size)** 
Writes a buffer of size characters to all enabled streams.
- **bool add(Print \* stream)** add another print stream. 
Returns false if no space left.


### Control

- **uint8_t count()** returns number of streams added, MAX 4 in initial release
- **uint8_t size()** returns size which is 4 in the current release.
- **uint8_t free()** returns number of free slots.
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
- **uint8_t index(Print \*stream)** returns the index of the stream if it was added,
otherwise it returns 0xFF == 255.  
Can be used to check if a stream is added the multiplexer.
- **Print \* stream(uint8_t index)** returns the stream at index or NULL otherwise.
Convenience function.


## Future

- set size in constructor - dynamic memory
- pack enabled flag in one or more bytes
- add names?
- remove a stream from the multiplex ?  
`bool remove(Print * stream); plus  bool remove(uint8_t idx) ?`
- iterate over the streams?   `Print * getStream(idx)`


## Operation

See examples
