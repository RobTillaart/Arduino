# Change Log AD985X

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.7.1] - 2024-05-24
- add support for ARDUINO_ARCH_MBED

## [0.7.0] - 2024-02-20
- Fix #33 AD9851::setRefClockHigh(), thanks to wh201906
- extended PR #32 to be more robust.

----

## [0.6.0] - 2024-02-04
- Fixed SW SPI interface, thanks to wh201906

----

## [0.5.0] - 2024-01-20
- Fix #28, improve handling SPI dependency.
- update examples

----

## [0.4.0] - 2023-11-27
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- reordered parameters software SPI constructor.
- update readme.md
- update examples

----

## [0.3.6] - 2023-10-15
- add ESP32 HSPI example
- add unit tests for setFrequency setFrequencyF
- update readme.md
- fix version number in .cpp
- minor edits

## [0.3.5] - 2023-01-11
- update GitHub actions
- update license
- add bool return value to setFrequency()
- add bool return value to setPhase()
- add test_constants in unit test

## [0.3.4] - 2022-10-25
- add changelog.md
- add RP2040 in build-CI
- add URL to examples

## [0.3.3] - 2021-12-10
- update library.json, license, readme.md
- fix reset() for ESP32 hardware SPI

## [0.3.2] - 2021-10-16
-  update Arduino-CI

## [0.3.1] - 2021-08-25
- VSPI / HSPI support for ESP32
- faster software SPI
- minor optimizations / refactor

## [0.3.0] - 2021-06-06
- fix factory bit mask
- add new examples
- some refactor
- added multi device document

----

## [0.2.2] - 2021-01-24
- add manual updating frequency
- get- setManualFQ_UD(), update()
- inverted SELECT line as preparation for multi-device.

## [0.2.1] - 2021-01-10
- add get- and setARCCutOffFreq()

## [0.2.0] - 2020-12-28
- major refactor class hierarchy + float frequency

----

## [0.1.2] - 2020-12-27
- add setAutoMode() + offset

## [0.1.1] - 2020-12-09
- add Arduino-CI

## [0.1.0] - 2019-03-19
- initial version

