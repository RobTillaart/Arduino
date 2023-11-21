# Change Log runningAngle

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.1] - 2023-11-21
- update readme.md


## [0.2.0] - 2023-02-22
- add **void setMode0()** ==> -180..180
- add **void setMode1()** ==> 0..360
- add **uint8_t getMode()** return 0 or 1.
- add RA_DEFAULT_WEIGHT to **setWeight()**
- change return type of **setWeight()** to bool (return false if clipped).
- add RA_MIN_WEIGHT + RA_MAX_WEIGHT as constants
- add examples
- update readme.md
- move code from .h to .cpp
- update GitHub actions
- update license 2023
- minor edits

----

## [0.1.5] - 2022-11-23
- add changelog.md
- add RP2040 to build-CI
- minor edits

## [0.1.4] - 2022-05-29
- add GRADIANS support

## [0.1.3] - 2021-12-28
- update library.json, readme, license,
- minor edits

## [0.1.2] - 2021-05-27
- Arduino-lint

## [0.1.1] - 2021-01-07
- Arduino-CI + unit test

## [0.1.0] - 2020-10-28
- initial version (based on code of Edgar Bonet)

