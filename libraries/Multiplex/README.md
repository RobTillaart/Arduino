
[![Arduino CI](https://github.com/RobTillaart/Multiplex/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Multiplex/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Multiplex.svg?maxAge=3600)](https://github.com/RobTillaart/Multiplex/releases)


# Multiplex

Arduino Library implementing a stream multiplexer.


## Description

Multiplex is a library in which one can add multiple Print streams. 
If one prints to the multiplexer it is sent to all the streams that were added.
The maximum nr of streams to add is 4 .
It is possible to disable individual streams.


## Interface


### Constructor

- **Multiplex()** constructor
- **void reset()** resets to zero streams in the multiplexer.

### Core

- **size_t write(uint8_t c)** workhorse of the print interface.
- **bool add(Print \* stream)** add another print stream. 
Returns false if no space left.


### Control

- **uint8_t count()** returns # streams, MAX 4 in initial release
- **uint8_t size()** returns size which is 4 in the current release.
- **void enable(uint8_t index)** enable the stream at index.
- **void disable(uint8_t index)** disable the stream at index.
- **bool isEnabled(uint8_t index)** checks if the stream at index is enabled.


## Future

- set size in constructor
- add names?
- bool inMp(stream)
- add returns int index?  or 0xFF for fail
- remove a stream from the multiplex ???  => complexer admin.
- increase up to 8 streams. (pack enabled flag in one byte)


## Operation

See examples
