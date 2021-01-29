
[![Arduino CI](https://github.com/RobTillaart/ANSI/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ANSI/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ANSI.svg?maxAge=3600)](https://github.com/RobTillaart/ANSI/releases)


# ANSI

Arduino library with basic ANSI display codes for terminal applications.


# Description

TODO

Ansi codes are special codes that are send to a terminal e.g. VT100 to add 
attributes to displayed characters. 
Typical examples are bold, blink or color. 
Also known as escape codes the set of codes is large, however not 
all terminal types do support all codes. 

Sending these ANSI codes to a simple terminal like the one in the Arduino
IDE might result in garbage. SO use with care.


## Terminals tested

Tests are done with 
- Teraterm 4.102 (vt100 mode)
- Putty 0.71 

Other terminal programma's exist so please let me know if yours is working too.
If not, please open an issue.

# Operation

See examples
