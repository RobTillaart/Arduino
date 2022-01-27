
[![Arduino CI](https://github.com/RobTillaart/FLETCHER/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FLETCHER/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FLETCHER/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FLETCHER/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FLETCHER/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FLETCHER/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FLETCHER.svg?maxAge=3600)](https://github.com/RobTillaart/FLETCHER/releases)


# FLETCHER

Arduino Library for Fletcher's checksum


## Description

This library provides a Fletcher checksum of a data array.

Fletcher's checksum is in general faster than CRC but possibly not as 
good in detecting errors.
See https://en.wikipedia.org/wiki/Fletcher%27s_checksum for details.

Relates to https://github.com/RobTillaart/CRC

Use https://github.com/RobTillaart/printHelpers to print the Fletcher64().

Tested on Arduino UNO only.


## Interface


## Fletcher16

These interfaces are very similar for Fletcher16, Fletcher32 and Fletcher64 class.

Use **\#include "Fletcher16.h"**

- **Fletcher16()** Constructor, initializes internals.
- **void begin(uint8_t s1 = 0, uint8_t s2 = 0)** resets the internals.
optional setting start values for s1 and s2. Note this is not part of the standard.
- **void add(uint8_t value)** add a single value to the checksum.
- **void add(const uint8_t \* array, uint8_t length)** add an array of values to the checksum.
- **uint16_t getFletcher()** get the current checksum.
- **uint32_t count()** get the number of items added. Merely a debugging feature, can overflow without affecting checksum.

The checksum from **getFletcher()** can be split into a high and a low part 
to be used to "feed" **begin()** again. See restart example.


#### Performance

Not tested ESP32 (and many other platforms) yet.
First numbers of **.add(value)** measured with test sketch shows the following timing.

| Checksum    |  UNO 16 MHz | ESP32 240 MHz |
|:------------|:-----------:|:-------------:|
| Fletcher16  |     3.8 us  |               |
| Fletcher32  |     5.6 us  |               |
| Fletcher64  |    10.1 us  |               |
| Average     |     6.5 us  |               |


## Interface static functions

The functions are straightforward, however one should define **length**
in terms of the data type and optional pad it with zeros.

A string "abcdef" has length 2 for **fletcher64()** as it needs 2x4 bytes.

Use **\#include "Fletcher.h"**

- **uint16_t fletcher16(uint8_t \*data, uint16_t length)** length in units of 1 byte = 8 bits.
- **uint32_t fletcher32(uint16_t \*data, uint16_t length)** length in units of 2 bytes = 16 bits.
- **uint64_t fletcher64(uint32_t \*data, uint16_t length)** length in units of 4 bytes = 32 bits.


#### Performance


Not tested extensively, first numbers of **.add(array, length)**
measured with **Fletcher_performance.ino** sketch shows the following timing.

Lorem Ipsum text = 868 bytes.

| Checksum    |  UNO 16 MHz | ESP32 240 MHz |
|:------------|:-----------:|:-------------:|
| Fletcher16  |    1120 us  |               |
| Fletcher32  |     728 us  |               |
| Fletcher64  |    1952 us  |               |
| Average     |    1267 us  |               |

Average 1267 / 868 = ~1.5 us per byte.


## Operation

See examples.


## Future ideas

- improve documentation
- test other platforms
- others e.g. Fletcher24?
- generic FletcherN(). for N = 1..32
- add Print interface
  - or Printable() ?
  - Stream ??
- add getters for S1 and S2 in the classes
- add parameter for start values for F in static functions
  - would allow to use them in a stream too.


