
[![Arduino CI](https://github.com/RobTillaart/SHEX/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/SHEX/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/SHEX.svg?maxAge=3600)](https://github.com/RobTillaart/SHEX/releases)


# SHEX

Arduino library to generate hex dump over Serial (any stream)


## Description

SHEX is a simple library that wraps the Serial output side (by default) and
generates an hexdump of all data that is printed. 16 bytes per row.

The default output format is 
```
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx

0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx 
```
with a separator line after each 8th line.

The constructor has a length parameter which can be used to have another
number of bytes per row. After construction this cannot be changed, at
least not in this initial release. 

The only thing one can toggle is HEX output or pass through by means 
of **setHEX(bool)**.
This makes it possible to switch between the modes e.g. between 
'debugging' and 'release' mode.


## Interface

### Constructor + Core

- **SHEX(Print \* stream = &Serial, uint8_t len = 16)** Constructor, optional set the number of bytes per line.
- **size_t write(uint8_t c)** implements the Print interface

### Modifiers

- **void setHEX(bool hexOutput = true)** switch between modi, HEX (true) or passthrough (false).
- **bool getHEX()** get modi set above.
- **void setBytesPerLine(uint8_t len = 16)** idem, default 16 bytes per line, forced multiple of 4.
- **uint8_t getBytesPerLine()** returns number of bytes per line.
- **void setSeparator(char c = ' ')** set the character.
- **char getSeparator()** return the character set.
- **void setCountFlag(bool flag = true)** show the character count at begin of every line.
- **bool getCountFlag()** return flag set.


## Future

Although no follow up release is planned, some ideas are kept here
so they won't get lost.

- Optional ASCII colomn in the output format ( . if not printable) e.g.
```
0xABCDABCD  xx xx xx xx xx xx xx xx xx    c.cc c..c
```
needs line buffering
- seperarator: runtime configurable; 
- headerline: runtime configurable; optional combined with separator
- HEX reader: converts dump format to a normal stream again.
- better name for the class?


## Operational

See examples
