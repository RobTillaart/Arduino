
[![Arduino CI](https://github.com/RobTillaart/SHEX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/SHEX/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/SHEX/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/SHEX/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/SHEX/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/SHEX.svg)](https://github.com/RobTillaart/SHEX/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHEX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHEX.svg?maxAge=3600)](https://github.com/RobTillaart/SHEX/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/SHEX.svg)](https://registry.platformio.org/libraries/robtillaart/SHEX)


# SHEX

Arduino library to generate hex dump over Serial (any stream).


## Description

### SHEX

**SHEX** is a simple library that wraps the Serial output side (by default) and
generates an hex dump of all data that is printed. 16 bytes per row.

The default output format is (changed since 0.3.0)
```
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx

ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx 
```

with a separator line after each 8th line.

The constructor has a length parameter which can be used to have another number of bytes per row.
This can be changed with **setBytesPerLine()**.

One can toggle HEX output or pass through by means of **setHEX(bool)**.
This makes it possible to switch between the modes e.g. between 'debugging' and 'release' mode.

One can toggle the character count at the start of the line.


### SHEXA

**SHEXA** (Serial HEX ASCII) is a derived class from **SHEX** that also 
displays a column with printable characters.


The default output format is 
```
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx  abcdefgh ijklmnop
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx  abcdefgh ijklmnop
ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx  abcdefgh ijklmnop

ABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx  etc
```

To print this ASCII column extra RAM and code is used. 
Therefore this is made a derived class from **SHEX**.

Furthermore **SHEXA** has a function **flushASCII()** to flush the ASCII column to output.
This is needed when HEX output is restarted.


## Interface

```cpp
#include "SHEX.h"
```

The **SHEX** and **SHEXA** share most of their interface.

### Defines

To be adjusted via command line (or in SHEX.h file)

|  define               |  value  |
|:----------------------|--------:|
|  SHEX_DEFAULT_LENGTH  |     16  |
|  SHEX_MAX_LENGTH      |     32  |
|  SHEX_MIN_LENGTH      |      4  |
|  SHEX_COUNTER_DIGITS  |      4  |
|  SHEX_DEFAULT_VTAB    |      8  |


### Constructor + Core

- **SHEX(Print \* stream = &Serial, uint8_t length = SHEX_DEFAULT_LENGTH)** Constructor, 
optional set the number of bytes per line.
default 16 bytes per line, forced multiple of 4, max SHEX_MAX_LENGTH = 32.
- **size_t write(uint8_t c)** implements the Print interface.


### Output Modifiers

- **void setHEX(bool hexOutput = true)** switch between modi, HEX (true) or pass through (false).
- **bool getHEX()** returns mode set above.
- **void setBytesPerLine(uint8_t length = SHEX_DEFAULT_LENGTH)** idem, default 16 bytes per line, 
forced multiple of 4, max SHEX_MAX_LENGTH = 32.
- **uint8_t getBytesPerLine()** returns number of bytes per line.


### Separator

- **void setSeparator(char c = ' ')** set the separator character, default a space.
Some people like a dot '.', or a tab '\t'. Feel free to experiment.
- **char getSeparator()** return the separator character set.


### Counter

- **void setCountDigits(uint8_t digits)** set the length of the counter, 8 or 6 or 4 (default). 
Other numbers will be rounded up to 4, 6 or 8.
- **uint8_t getCountDigits()** returns idem.
- **void restartOutput()** restarts the counter from 0 and a new line.
Is automatically called if a setting is modified like **bytesPerLine**
**setVTAB** or **setCountDigits**
- **uint32_t getCounter()** return internal counter.


### VTAB

- **void setVTAB(uint8_t vtab = SHEX_DEFAULT_VTAB)** set the vertical separator line. 
- **uint8_t getVTAB()** return the current vertical separator line.


### SHEXA specific

- **void flushASCII()** allows the user to flush the ASCII column to output.
This is typically used after a setting is changed, which causes a restart of
the HEX output. Best if followed by a **restartOutput()**.
_Note: it is not ideal but workable. This might change in the future._


## Operational

See examples.


## Future

#### Must

- documentation

#### Should

- optimize code
  - print vs write
- more testing
  - performance measurement
  - different platforms. 
  - different streams incl SW Serial

#### Could

- investigate **flushASCII()** performance.
- HEX reader: **RHEX** 
  - converts dump format to a binary or ASCII stream.
  - separate library.
- **void setSeparatorInterval()**
- add examples

#### Wont

- line buffering for faster output (e.g Ethernet and SD card)
  could it support **write(array, length)** call.
  needs quite a rewrite..
  Needs a big buffer: ~150 bytes. (counter 8 + hex 96 + printable 32 + extra sep)
  ==> go through a small buffer twice as data is same!!
- header line: runtime configurable; 
  optional combined with separator
  and after how many lines the header should repeat
  **header(str, lines)** ?
  Can also be done by just calling Serial.print.


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

