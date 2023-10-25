# Change Log DHTlib

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.36] - 2023-10-25
- update readme.md
- create changelog.md
- minor edits


# [0.1.35] - 2021-12-16
- update library.json, license, #pragma once,
- move private defines to .cpp file

# [0.1.34] - 2021-11-13
- fix negative temperature DHT22 again (code from DHTNew)

# [0.1.33] - 2021-02-16
- fix #6 T-GO signal in handshake. (needed for long wires)

# [0.1.32] - 2021-02-01
- fix negative temperature DHT22 again (code from DHTNew)

# [0.1.31] - 2020-12-15
- fix negative temperature DHT22 (code from DHTNew)

# [0.1.30] - 2020-06-30
- own repo;

# [0.1.29] - 2018-09-02
- fix negative temperature DHT12 - issue #111

# [0.1.28] - 2018-04-03
- refactor

# [0.1.27] - 2018-03-26
- added _disableIRQ flag

# [0.1.26] - 2017-12-12
- explicit support for AM23XX series and DHT12

# [0.1.25] - 2017-09-20
- FIX https://github.com/RobTillaart/Arduino/issues/80

# [0.1.24] - 2017-07-27
- FIX https://github.com/RobTillaart/Arduino/issues/33  double -> float

# [0.1.23] - 2017-07-24
- FIX https://github.com/RobTillaart/Arduino/issues/31


----

## Older

//  0.1.22   undo delayMicroseconds() for wakeups larger than 8
//  0.1.21   replace delay with delayMicroseconds() + small fix
//  0.1.20   Reduce footprint by using uint8_t as error codes. (thanks to chaveiro)
//  0.1.19   masking error for DHT11 - FIXED (thanks Richard for noticing)
//  0.1.18   version 1.16/17 broke the DHT11 - FIXED
//  0.1.17   replaced micros() with adaptive loopcount
//           removed DHTLIB_INVALID_VALUE
//           added  DHTLIB_ERROR_CONNECT
//           added  DHTLIB_ERROR_ACK_L  DHTLIB_ERROR_ACK_H
//  0.1.16   masking unused bits (less errors); refactored bits[]
//  0.1.15   reduced # micros calls 2->1 in inner loop.
//  0.1.14   replace digital read with faster (~3x) code => more robust low MHz machines.
//
//  0.1.13   fix negative temperature
//  0.1.12   support DHT33 and DHT44 initial version
//  0.1.11   renamed DHTLIB_TIMEOUT
//  0.1.10   optimized faster WAKEUP + TIMEOUT
//  0.1.09   optimize size: timeout check + use of mask
//  0.1.08   added formula for timeout based upon clockspeed
//  0.1.07   added support for DHT21
//  0.1.06   minimize footprint (2012-12-27)
//  0.1.05   fixed negative temperature bug (thanks to Roseman)
//  0.1.04   improved readability of code using DHTLIB_OK in code
//  0.1.03   added error values for temp and humidity when read failed
//  0.1.02   added error codes
//  0.1.01   added support for Arduino 1.0, fixed typos (31/12/2011)
//  0.1.00   initial version by Rob Tillaart (01/04/2011)

