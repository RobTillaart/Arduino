# Change Log Cozir

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.8] - 2024-04-11
- update GitHub actions
- minor edits

## [0.3.7] - 2023-10-19
- update readme.md (badges)
- redo changelog.md layout

## [0.3.6] - 2022-10-30
- add RP2040 to build-CI
- minor edits

## [0.3.5] - 2022-02-25
- added capturing mode 'K' field in the COZIRParser class
- added all known fields in the COZIRParser class
- added sending commands in stream parser example to test.
- added example with adaptive timing depending on CO21 level.
- verify requested field in **\_request()**
- minor edits.

## [0.3.4] - 2022-02-22
- added COZIRParser class for streaming mode
- added streaming examples
- minor edits

## [0.3.3] - 2022-02-21
- update readme.md
- update + add examples
- tested with GC0034
- changed return value of **setOperatingMode()** to bool.
- refactor

## [0.3.2] - 2021-12-14
- update library.json
- license, minor edits

## [0.3.1] - 2021-10-20
- update Arduino-CI
- badges in readme.md

## [0.3.0] - 2021-08-08
- Major update - breaks interface (names mainly)
- add **isInitialized()**
- add **getOperatingMode()**
- add **getOutputFields()**
- add **inOutputFields()**
- add **kelvin()**
- add EEPROM functions
- class methods camelCase
- extend unit tests

----

## [0.2.6] - 2021-01-31
- fix #4 use Mode0 for versions and configuration

## [0.2.5] - 2020-12-26
- fix software Serial + version number (oops)

## [0.2.2] - 2020-12-17
- add Arduino-CI + unit tests

## [0.2.1] - 2020-06-05
- fix library.json

## [0.2.0] - 2020-03-30
- some refactor and own repo

-----

## [0.1.06]
- added support for HardwareSerial for MEGA
- removed support for NewSoftSerial
- stop pre 1.0 support)

## [0.1.05]
- fixed bug uint16_t request() to uint32_t request() in .h file

## [0.1.04]
- changed CO2 to support larger values

## [0.1.03]
- added setOperatingMode

## [0.1.02]
- added support Arduino 1.x

## [0.1.01] - 2012-??-??
- initial version

