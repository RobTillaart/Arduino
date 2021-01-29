
[![Arduino CI](https://github.com/RobTillaart/IEEE754tools/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/IEEE754tools/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/IEEE754tools.svg?maxAge=3600)](https://github.com/RobTillaart/IEEE754tools/releases)


# IEEE754tools

Arduino library to manipulate IEEE754 float numbers fast.

## Description

IEEE754tools.h contains a collection of bit-hacks to speed up a number 
of operations on floating point numbers on the Arduino. These bit-hacks
started in 2010 (oldest code found) or maybe even earlier.

http://en.wikipedia.org/wiki/Double_precision

http://en.wikipedia.org/wiki/Single-precision_floating-point_format


## WARNING

- If you don't need micro-second speedups **do not use** these code snippets.
- code is experimental, so use with care.
- only tested on UNO

## Future

- investigate other speedups
- write more examples
- test on ESP32
- test with double
- binary transfer over Serial

## Operations

See examples

