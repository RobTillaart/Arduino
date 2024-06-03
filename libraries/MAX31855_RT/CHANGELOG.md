# Change Log MAX31855_RT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.1] - 2024-06-03
- add support for ARDUINO_ARCH_MBED

## [0.6.0] - 2024-01-19
- Fix #31, improve SPI dependency

----

## [0.5.0] - 2023-11-29
- refactor constructor/begin interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.4.4] - 2023-11-11
- update readme.md

## [0.4.3] - 2023-02-26
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.4.2] - 2022-11-16
- add RP2040 in build-CI
- add changelog.md
- minor edit readme.md
- minor edit unit test

## [0.4.1] - 2021-12-10
- add SWSPI delay + getter/setter

## [0.4.0] - 2021-12-09
- fix #21 breaking change for HW SPI
- move constructor code to begin()
- read() removed "premature" return on status.

----

## [0.3.0] - 2021-08-11
- VSPI / HSPI support for ESP32
- add setGIOpins - ESP32 specific
- add get/setSPIspeed() - all

----

## [0.2.5] - 2021-07-04
- fix #14 CS for STM32.

## [0.2.4] - 2020-12-30
- arduinoCI, unit test

## [0.2.3] - 2020-08-30
- fix #8 support hardware SPI + example

## [0.2.2] - 2020-08-30
- fix #9
- fix failing examples
- minor refactor

## [0.2.1] - 2020-08-26
- read rawData and STATUS_NO_COMMUNICATION recognition (thanks to FabioBrondo)

## [0.2.0] - 2020-06-20
- add #pragma once
- major refactor
- remove pre 1.0 support
- fix offset

----

## [0.1.10] - 2019-07-31
- add 3 inline functions to test errors
- add demo sketch

## [0.1.9] - 2017-07-27
- fix #33 reverted double -> float

## [0.1.08] - 2015-12-06
- replaced all temperature calls with one TCfactor
- update demos.

## [0.1.07] - 2015-12-06
- updated TC factors from the MAX31855 datasheet

## [0.1.06] - 2015-12-05
- added support for other types of TC's (experimental)

## [0.1.05] - 2015-07-12
- refactor robust constructor.

## [0.1.04] - 2015-03-09
- replaced float -> double (ARM support).

## [0.1.03] - 2014-01-24
- fixed negative temperature.

## [0.1.02] - 2014-01-03
- added offset.

## [0.1.01] - 2014-01-02
- refactored speed/performance.

## [0.1.00] - 2014-01-02
- initial version.

