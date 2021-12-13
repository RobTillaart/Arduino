
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
Typical examples are bold, blink or colour. 
Also known as escape codes the set of codes is large, however not 
all terminal types do support all codes. 

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


## Performance

Since 0.1.5 there is some focus on performance. 
Using **ansi.print()** and **ansi.println()** for printing text and numbers is 
improved a bit since 0.1.4 by adding the private **write(array, length)**.


## Future

- test more terminal programs (Linux mac)
- write more examples
  - DOS emulator?
- increase functionality
  - which codes are useful ?
- investigate performance. (first step made in 0.1.5 but more possible)
  - add line buffer in write(c) to improve throughput?
  - need for flush() with line buffer?
  - rewrite functions, replace print() by **\_stream->write()** calls?  (effect on size?)

