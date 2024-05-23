# Change Log DAC8552

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.5.1] - 2024-05-22
- improve support for ARDUINO_ARCH_MBED


## [0.5.0] - 2024-01-20
- Fix #16, improve handling SPI dependency.
- update examples

----

## [0.4.0] - 2023-12-09
- Fix #14 bug, buffer select for B channel. Kudos to sjthomsen.
  - invalidates all previous versions.

----

## [0.3.0] - 2023-12-01
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.2.5] - 2023-10-19
- update readme.md (badges)

## [0.2.4] - 2022-10-30
- add changelog.md
- add rp2040 to build-CI

## [0.2.3] - 2021-12-15
- update library.json
- update license
- update unit test
- minor edits

## [0.2.2] - 2021-08-29
- add support for HSPI / VSPI ESP32 ++

## [0.2.1] - 2021-06-02
- compile ESP32 + fix for channel B

## [0.2.0] - 2020-12-18
- add arduino-ci + unit test
- add slave select pin for HW constructor

----

## [0.1.3] - 2020-06-07
- fix library.json

## [0.1.2] - 2020-04-06
- minor refactor
- update readme.md

## [0.1.1] - 2017-12-19
- fix begin() bug

## [0.1.0] - 2017-12-14
- initial version

