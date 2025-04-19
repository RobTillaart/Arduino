# Change Log AD5680

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2025-04-12
- fix SPI mode 1 (See #12 AD5620)
- sync AD5660/20
- add **getMaxValue()**
- fix readme table layout
- minor edits

----

## [0.3.2] - 2025-01-20
- redo SW SPI, see PR #4 AD5660 library

## [0.3.1] - 2024-05-23
- add support for ARDUINO_ARCH_MBED

## [0.3.0] - 2024-01-19
- Fix #7, improve handling SPI dependency.

----

## [0.2.1] - 2024-01-02
- fix examples
- add __SPI_CLASS__ guard
- minor edits

## [0.2.0] - 2023-11-26
- refactor constructor interface - breaking changes.
  - minimize conditional code. -- create SPI_CLASS macro to solve it.
- reordered parameters software SPI constructor.
- update readme.md
- update examples

----

## [0.1.1] - 2023-09-22
- fix SPI_MODE to SPI_MODE0 for hardware SPI.
- fix **updateDevice()**
- add **AD5680_triangle.ino** example
- add **AD5680_sawtooth.ino** example


## [0.1.0] - 2023-09-19
- initial version

