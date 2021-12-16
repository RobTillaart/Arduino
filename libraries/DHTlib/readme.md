
[![Arduino CI](https://github.com/RobTillaart/DHTlib/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DHTlib/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DHTlib/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DHTlib/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DHTlib/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DHTlib/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DHTlib.svg?maxAge=3600)](https://github.com/RobTillaart/DHTlib/releases)


# DHTlib

Arduino library for DHT temperature and humidity sensor. AVR optimized


## Description

The DHT11, 21, 22, 33 and 44 are relative inexpensive sensors for measuring temperature and humidity.

This library can be used for reading both values from these DHT sensors.
The DHT11 only returns integers (e.g. 20) and does not support negative values.
The others are quite similar and provide one decimal digit (e.g. 20.2)
The hardware pins of the sensors and handshake are identical so ideal to combine in one lib.

The library (0.1.13 version) is confirmed to work on:

- UNO (tested myself)
- 2009 (tested myself)
- MEGA2560
- DUE
- attiny85 @8MHz
- Digistump Digix @ 84 MHz

Later 0.1.xx versions are optimized for AVR only.

More information - http://playground.arduino.cc/Main/DHTLib -

For latest version for the DHT, check https://github.com/RobTillaart/DHTNEW


## DHT PIN layout from left to right

| Front |      | Description   |
|:------|:----:|:--------------|
| pin 1 |      | VCC           |
| pin 2 |      | DATA          |
| pin 3 |      | Not Connected |
| pin 4 |      | GND           |



## Operational

See examples


## Versions:

==> See DHTStable library for latest stable version for all platforms.

- version 0.1.13 is the last stable version for both AVR and ARM 
- version 0.1.14 and up are not compatible any more with pre 1.0 Arduino. 
These have breaking changes wrt ARM based Arduino's e.g DUE.
- version 0.1.15 is stable version for AVR only
- version 0.1.16 and 0.1.17 have breaking changes for DHT11
- version 0.1.18 works again for DHT11 (AVR only)
- version 0.1.19 fixed masking bug DHT11 (AVR only)
- version 0.1.20 Reduce footprint (34 bytes) by using int8_t as error codes. (thanks to chaveiro)
- version 0.1.21 replace delay with delayMicroseconds() + small fix (thanks to codingforfun)
- version 0.1.22 undo delayMicroseconds() for wakeups larger than 8
- version 0.1.23 fix https://github.com/RobTillaart/Arduino/issues/31
- version 0.1.24 fix https://github.com/RobTillaart/Arduino/issues/33
- version 0.1.25 fix https://github.com/RobTillaart/Arduino/issues/80
- version 0.1.26 Explicit support for AM23XX series and DHT12
- version 0.1.27 added \_disableIRQ flag
- version 0.1.28 refactor
- version 0.1.29 fix negative temperature DHT12 - issue #111
- version 0.1.30 own repo version
- version 0.1.31 fix negative temperature DHT22 (code from DHTNew)
- version 0.1.32 fix negative temperature DHT22 again (code from DHTNew)
- version 0.1.33 fix #6 T-GO signal in handshake. (needed for long wires)
- version 0.1.34 fix negative temperature DHT22 again (code from DHTNew)
- version 0.1.35 update license, library.json, #pragma once, minor edits


## Future

- updates only on request basis (bugs)
- improve documentation
- improve unit tests
  - constants
- move non public part of #defines to .cpp
- separate history versions releasenotes file ?
- 

