# Change Log AD520X

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.1] - 2024-05-23
- add support for ARDUINO_ARCH_MBED

## [0.5.0] - 2024-01-19
- Fix #23, improve handling SPI dependency.
- add SPIClass guard

----

## [0.4.0] - 2023-11-26
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.3.2] - 2023-10-13
- update readme.md
- minor edits

## [0.3.1] - 2023-01-10
- update GitHub actions
- update license
- add setGroupValue(mask, value)
- add setGroupPercentage(mask, percentage)
- move all code to .cpp file

## [0.3.0] - 2022-10-12
- Fix 13 shutdown / reset. (kudos to Ale11Re)
- Fix 14 wrong SPI mode. (kudos to Ale11Re)
- Add RP2040 support to build-CI.
- Add CHANGELOG.md

----

## [0.2.2] - 2022-09-19
- update readme.md
- add "stereo functions" for setting 2 channels in one call
- setValue() and setPercentage()
- performance update.

## [0.2.1] - 2021-12-10
- update library.json,
- update licence
- default value for setAll()

## [0.2.0] - 2021-10-16
- update build-CI
- add get- and setPercentage()

----

## [0.1.2] - 2021-08-19
- VSPI / HSPI support for ESP32 only
- add setGPIOpins for ESP32 only
- add SetSPIspeed (generic)

## [0.1.1] - 2020-12-08
- Arduino-CI + unit test
- add isPowerOn()

## [0.1.0] - 2020-07-26
- refactor,
- fix #2 select pin for HW SPI;
- add shutdown().

## [0.0.2] - 2020-07-25
- support for AD8400 series in documentation

## [0.0.1] - 2020-07-24
- initial version

