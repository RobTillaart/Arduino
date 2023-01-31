
[![Arduino CI](https://github.com/RobTillaart/ANSI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ANSI/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ANSI/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ANSI/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ANSI/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ANSI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ANSI.svg?maxAge=3600)](https://github.com/RobTillaart/ANSI/releases)


# ANSI

Arduino library with basic ANSI display codes for terminal applications.


# Description

ANSI codes are special codes that are send to a terminal e.g. VT100 to add
attributes to displayed characters.
Typical examples are bold, blink or colour. ANSI codes are also known as escape codes.
The set of codes is large, however not all terminal types do support all codes.

Sending these ANSI codes to a simple ASCII only terminal like the one in the Arduino
IDE might result in garbage. So use with care.


## Terminals tested

Tests are done with
- TeraTerm 4.102 + 4.106 (VT100, VT202, VT525 mode)
- Putty 0.71

Other terminal program's exist so please let me know if yours is working too.
If not, please open an issue.


## Operation

See examples


## Interface

```cpp
#include "ansi.h"
```

#### Constructor

- **ANSI(Stream \* stream = &Serial)** wrapper around Serial.
Can be a software serial too.


#### Stream interface

- **int available()**
- **int read()**
- **int peek()**
- **void flush()**

Stream interface also includes print(), println(), write().


#### Character modi

- **void normal()** idem.
- **void bold()** idem.
- **void low()** idem.
- **void underline()** idem.
- **void blink()** idem.
- **void reverse()** idem.


#### Colour

- **void foreground(uint8_t fgcolor)**
- **void background(uint8_t bgcolor)**
- **void color(uint8_t fgcolor, uint8_t bgcolor)**
- **uint8_t gray2color(uint8_t gray)**
- **uint8_t grey2color(uint8_t grey)** idem
- **uint8_t rgb2color(uint8_t r, uint8_t g, uint8_t b)**


todo colour table


#### Positioning

- **void clearScreen()**
- **void clearLine(uint8_t clear = toEnd)** toEnd = 0,
  toStart = 1,en tireLine = 2,
- **void home()** go to 0,0
- **void gotoXY(uint8_t x, uint8_t y)**
- **void cursorUp(uint8_t x)**
- **void cursorDown(uint8_t x)**
- **void cursorForward(uint8_t x)**
- **void cursorBack(uint8_t x)**


#### Experimental

look into **ansi.h** for experimental functions and notes.

Version 0.1.6 added a number of experimental function that need more testing.
Some are working with Teraterm, others are unclear of fail.
The user can uncomment these and verify if these work with their terminal.

Also added is the **int deviceType()** function which also need more testing.

As always, constructive feedback is welcome.


## Performance

Since 0.1.5 there is some focus on performance.
Using **ansi.print()** and **ansi.println()** for printing text and numbers is
improved a bit since 0.1.4 by adding the private **write(array, length)**.


## Future

#### Must

- improve documentation
  - elaborate interface
  - colour info

#### Should

- test experimental functions
- test more terminal programs (Linux mac)
- add examples
  - DOS emulator?
  - experimental section

#### Could

- increase functionality
  - which codes are generic / useful ?
- investigate performance.
  - first step made in 0.1.5 but more possible
  - add line buffer in write(c) to improve throughput?
  - need for flush() with line buffer?
  - rewrite functions, replace print() by **\_stream->write()** calls?  (effect on size?)
  - move static strings to PROGMEM? as defines?
    roughly ~20 bytes progmem for 4 bytes RAM...
  - print(char) iso print(string) where possible


#### Wont


