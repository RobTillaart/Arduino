
[![Arduino CI](https://github.com/RobTillaart/Adler/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Adler/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Adler/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Adler/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Adler/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Adler/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Adler.svg?maxAge=3600)](https://github.com/RobTillaart/Adler/releases)


# Adler

Arduino Library for Adler-32 checksum


## Description

This library provides a Adler checksum of a data array.

Relates to https://github.com/RobTillaart/CRC

Relates to https://github.com/RobTillaart/Fletcher

Tested on Arduino UNO only.


## Interface


## Adler class

Use **\#include "Adler.h"**

- **Adler32()** Constructor, initializes internals.
- **void begin(uint8_t s1 = 1, uint8_t s2 = 0)** resets the internals.
optional setting start values for s1 and s2. Note this is not part of the standard.
This allows a restart from a specific index in a buffer.
- **void add(uint8_t value)** add a single value to the checksum.
- **void add(const uint8_t \* array, uint8_t length)** add an array of values to the checksum.
- **uint32_t getAdler()** get the current checksum.
- **uint32_t count()** get the number of items added. Merely a debugging feature, can overflow without affecting checksum.

The class is typically used for streaming very large blocks of data,
optional with intermediate checksum tests.


#### Performance

Not tested ESP32 (and many other platforms) yet.
First numbers of **.add(value)** measured with test sketch shows the following timing.

| Checksum    |  UNO 16 MHz | ESP32 240 MHz |
|:------------|:-----------:|:-------------:|
| Adler32     |     5.6 us  |               |



## Interface static functions

The function is straightforward.

Use **\#include "Adler.h"**

- **uint32_t adler32(uint8_t \*data, uint16_t length)** length in units of 1 byte = 8 bits.

The function is typically used for an in memory buffer to calculate 
the Adler checksum once.


#### Performance


Not tested extensively, first numbers of **.add(array, length)**
measured with **Adler_performance.ino** sketch shows the following timing.

Lorem Ipsum text = 868 bytes.

| Checksum    |  UNO 16 MHz | ESP32 240 MHz |
|:------------|:-----------:|:-------------:|
| Adler32     |   1116 us   |               |

Average 1116 / 868 = 1.29 us per byte.


## Operation

See examples.


## Future ideas

- test other platforms
- optimize add(array, length) ..


