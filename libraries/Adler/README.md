
[![Arduino CI](https://github.com/RobTillaart/Adler/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/Adler/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/Adler/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/Adler/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/Adler/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/Adler.svg)](https://github.com/RobTillaart/Adler/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Adler/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Adler.svg?maxAge=3600)](https://github.com/RobTillaart/Adler/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/Adler.svg)](https://registry.platformio.org/libraries/robtillaart/Adler)


# Adler

Arduino Library for Adler-32 and experimental Adler-16 checksum.


## Description

This library provides an Adler32 checksum of a data block, typical an array of bytes.
Since 0.2.0 the library also supports an experimental Adler16 implementation.
This Adler16 is often faster as it uses a smaller checksum than the Adler32.
The price is that Adler16 is less sensitive than Adler32 as less possible checksums
are possible. 
Still it will have its niches where it will be useful.

0.2.0 is a breaking change, file names have been changed to be more
in line with the CRC library.
- Adler.h for the static functions
- Adler32.h for the Adler32 class
- Adler16.h for the Adler16 class.


#### Related

- https://en.wikipedia.org/wiki/Adler-32
- https://github.com/RobTillaart/Adler
- https://github.com/RobTillaart/CRC
- https://github.com/RobTillaart/Fletcher
- https://github.com/RobTillaart/LUHN


#### Tested

Tested on Arduino UNO and ESP32.


## Interface


### Adler class

```cpp
#include "Adler32.h"
// or 
#include "Adler16.h"
```

The interface for the Adler16 is very similar.

- **Adler32()** Constructor, initializes internals.
- **void begin(uint32_t s1 = 1, uint32_t s2 = 0)** resets the internals.
optional setting start values for s1 and s2. Note this is not part of the standard.
These parameters allows a restart from a specific index in a buffer.
- **void add(uint8_t value)** add a single value to the checksum.
- **uint32_t add(uint8_t \* array, uint16_t length)** add an array of values to the checksum.
Returns the current checksum.
- **uint32_t addFast(uint8_t \* array, uint16_t length)** add an array of values to the checksum.
Is faster by trading PROGMEM for performance.
Returns the current checksum.
- **uint32_t getAdler()** get the current checksum.
- **uint32_t count()** get the number of items added. Merely a debugging feature,
can overflow without affecting checksum.

The class is typically used for streaming very large blocks of data,
optional with intermediate checksum tests (e.g after every 256 bytes)

Wrappers exist for adding char and char array. Functional identical to above.

- **void add(char value)**
- **uint32_t add(char \* array, uint16_t length)**
- **uint32_t addFast(char \* array, uint16_t length)**


## Performance Adler32

Only tested on UNO and ESP32 yet.
If you have data of other platforms, please let me know.

Numbers measured with **Adler32_performance.ino**.


### add(value)

The **add(value)** adds one byte and does a subtraction
instead of a modulo.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.1.0   |   add    |   5.6 us   |               |
| 0.1.2   |   add    |   6.6 us   |               |
| 0.2.0   |   add    |   5.9 us   |    1.7 us     |


### add(lorem) 868 chars

The **add(array, length)** is a straightforward loop
over the array and has a small footprint.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.1.0   |   add    |            |               |
| 0.1.2   |   add    |  6392 us   |               |
| 0.2.0   |   add    |  5748 us   |     145 us    |


Note: **add()** is about 6.6 us per byte.


### addFast(lorem) 868 chars

The **addFast(array, length)** is faster than the
reference **add(array, length)** and uses 108 bytes more (UNO).
So the function has a larger footprint.
Depending on your needs, choose performance or footprint.

See **Adler32_performance_addFast.ino**


| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.1.0   | addFast  |            |               |
| 0.1.2   | addFast  |  1348 us   |               |
| 0.2.0   | addFast  |  1348 us   |      66 us    |

Note: **addFast()** is less than 2 us per byte.


## Performance Adler16

Only tested on UNO and ESP32 yet.
If you have data of other platforms, please let me know.

Numbers measured with **Adler16_performance.ino**.


### add(value)

The **add(value)** adds one byte and does a subtraction
instead of a modulo.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.2.0   | add      |   4.0 us   |     1.8 us    |


The per byte performance of the Adler16 (on UNO) is faster
than the Adler32 **add(value)**. The reason is that a 16 bit
subtraction on an UNO is faster than a 32 bit subtraction.


### add(lorem) 868 chars

The **add(array, length)** is a straightforward loop
over the array and has a small footprint.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.2.0   | add      |  4040 us   |    160 us     |

Note: **add()** is about 6.6 us per byte.


### addFast(lorem) 868 chars

The **addFast(array, length)** is faster than the
reference **add(array, length)**.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.2.0   | addFast  |  1968 us   |     79 us     |

The gain of the faster 16 bit modulo meets the frequency of
doing the modulo more often.


## Interface static functions

```cpp
#include "Adler.h"
```

The static functions are typically used for an in memory buffer to calculate the checksum once.
Think of packets in a network, records in a database, or a checksum for an configuration in EEPROM.

The functions are straightforward. Length is in bytes (8 bits).

- **uint32_t adler32(uint8_t \*data, uint16_t length, uint32_t s1 = 1, uint32_t s2 = 0)**
- **uint16_t adler16(uint8_t \*data, uint16_t length, uint16_t s1 = 1, uint16_t s2 = 0)**

Two wrapper functions added in 0.2.4 for char array's (convenience).

- **uint32_t adler32(char \*data, uint16_t length, uint32_t s1 = 1, uint32_t s2 = 0)**
- **uint16_t adler16(char \*data, uint16_t length, uint16_t s1 = 1, uint16_t s2 = 0)**


### Performance

Only tested on UNO and ESP32 yet.
If you have data of other platforms, please let me know.

Numbers measured with **Adler_performance.ino**.

Lorem Ipsum text = 868 bytes.

| Version | Function | UNO 16 MHz | ESP32 240 MHz |
|:-------:|:---------|:----------:|:-------------:|
| 0.1.0   | Adler32  |  1116 us   |               |
| 0.1.2   | Adler32  |  1116 us   |               |
| 0.2.0   | Adler32  |  1116 us   |     60 us     |
| 0.2.0   | Adler16  |  1736 us   |     75 us     |


#### UNO

Adler32 average 1116 / 868 = 1.29 us per byte.
Adler16 average 1736 / 868 = 2.00 us per byte. (~1.5x slower !)

Adler16 does more often the modulo math as it reaches halfway uint16_t
faster than Adler32 reaches halfway uint32_t.

As the Adler16 is less performant as the Adler32 (on all tested platforms),
Adler32 is often the best choice to use the 32 bit version.


## Operation

See examples.


## Future

#### Must

#### Should

- improve documentation
- redo performance testing
  - next major upgrade(0.3.0)
  - other platforms?
- extend unit tests
  - s1 s2 parameter static functions


#### Could

- Adler64 ?
  - would need a large prime (which) => 4294967291
  - max uint32_t       = 4.294.967.296
  - max uint32_t prime = 4.294.967.291
  - need printHelpers library for printing.
  - only on request.
- **void add(String str);**?


#### Wont

- do the string wrappers need strlen() ? parameter.
  - yes, as string can be processed partially.
- no return value for **add(value)**
  - would create too much overhead for repeated calls.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

