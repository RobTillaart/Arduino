# Change Log DAC8551

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2024-05-23
- add support for ARDUINO_ARCH_MBED

## [0.4.0] - 2024-01-20
- Fix #19, improve handling SPI dependency.
- update examples

----

## [0.3.0] - 2023-12-01
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- update readme.md
- update examples

----

## [0.2.7] - 2023-09-23
- add example DAC8531_hw_spi.ino + screenshot
- update readme.md
- minor edits

## [0.2.6] - 2022-10-31
- add changelog.md
- add rp2040 to build-CI

## [0.2.5] - 2021-12-15
- update library.json
- update license
- minor edits

## [0.2.4] - 2021-08-29
- add support for HSPI / VSPI ESP32 ++

## [0.2.3] - 2021-06-02
- compile ESP32

## [0.2.2] - 2021-02-04
- add DAC8550 DAC8501 DAC8501 derived class
- minor refactor

## [0.2.1] - 2020-12-18
- add arduino-ci + unit tests

## [0.2.0] - 2020-12-18
- add slaveSelect to hardware SPI

----

## [0.1.3] - 2020-06-07
- fix library.json
## [0.1.2] - 2020-04-06
- minor refactor
- update readme.md

## [0.1.1] - 2017-12-19
- fix begin() bug

## [0.1.0] - 2017-12-18
- initial version


