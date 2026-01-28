
[![Arduino CI](https://github.com/RobTillaart/wordCount/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/wordCount/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/wordCount/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/wordCount/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/wordCount/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/wordCount.svg)](https://github.com/RobTillaart/wordCount/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/wordCount/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/wordCount.svg?maxAge=3600)](https://github.com/RobTillaart/wordCount/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/wordCount.svg)](https://registry.platformio.org/libraries/robtillaart/wordCount)


# wordCount

Arduino library for creating a wordCounter.


## Description

**Experimental**

This library is a wordCount wrapper around an Arduino stream.
It allows to count the bytes, words and digits e.g. for Ethernet packets
that are **written**.
The counting is (for now) only done on the output (Print) side.

The internal counters can be requested after every print() or println() statement.
It is also possible to reset() the counters to zero at any moment.
statement

The idea is derived from the UNIX/Linux wordCount program wc.

This library is originally written for **educational** purpose.
As it might be useful, I decided to (clean up) and publish it.

Feedback as always is welcome.


### Related

Just other "stream wrapping" libraries

- https://github.com/RobTillaart/ANSI - Arduino library to send ANSI escape sequences
- https://github.com/RobTillaart/LineFormatter - Simple positioning wrapper class for Serial / Stream
- https://github.com/RobTillaart/logicAnalyzer - Arduino library for building a logicAnalyzer. (non performant).
- https://github.com/RobTillaart/Multiplex - Arduino Library implementing a Print stream multiplexer.
- https://github.com/RobTillaart/SHEX - Arduino library to generate hex dump over Serial
- https://github.com/RobTillaart/XMLWriter - Arduino Library to create simple XML
- https://github.com/RobTillaart/printHelpers - for big numbers.


### Tested

Example works on Arduino UNO. Not tested on other platforms.
Values seem to be correct so far, note println() can add both a \n and a \r,
so the char counter could be +1.


## Interface

```cpp
#include "wordCount.h"
```

### Constructor

- **wordCount(Stream \* stream = &Serial)** constructor
- **void reset()** - resets counters and start time for throughput measurements.

### Core

- **uint32_t chars()** idem.
- **uint32_t digits()** idem.
- **uint32_t lines()** idem.
- **uint32_t words()** idem.

### Throughput

- **float bytesPerSecond()** idem.
- **float Bps()** Bytes per second
- **float kBps()** kiloBytes per second
- **float MBps()** MegaBytes per second
- **float wordsPerSecond()** idem.
- **float linesPerSecond()** idem.

### Statistics

- **float averageCharsPerLine()** idem (includes \n\r).


## Future

#### Must

- improve documentation

#### Should

- add examples

#### Could

- investigate new functions.
  - average word length (difficult!)
  - add user defined counter e.g. count a user defined char e.g. @ or !
  - printable(), non-printable, ASCII, "above 127"
  - call back on user defined char / substring?
  - float averageCharsPerLine() corrected for \n\r?
- create unit tests. Lorum ipsum


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


