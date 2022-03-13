# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [1.0.0] - 2022-03-09

### Added

- CHANGELOG.md: moved history in Statistic.cpp to this file.

### Changed

- Turned this into a header-only library to make use of compiler
  inline optimizations.

- Turned this into a class template to reduce dead code at compile
  time and allow for the use of other floating point formats (double,
  long double for example).

### Fixed

- Replaced `#include <Arduino.h>` with `#include <cstdint>` to find
  the proper location of `uint32_t`.  This also allows one to use the
  library in non-Arduino environments.

## [0.4.4] - 2021-12-28

### Added

### Changed

- update library.json, readme, license, minor edits

## [0.4.3] - 2021-01-20

### Added

### Changed

- add() returns how much was actually added.

## [0.4.2] - 2021-01-08

### Added

- add Arduino-CI + unit tests

### Changed

## [0.4.1] - 2020-06-19

### Added

### Changed

- fix library.json

## [0.4.0] - 2020-05-13

- refactor

### Added

- Added flag to switch on the use of `stdDev` runtime. [idea marc.recksiedl]

### Changed

## [0.3.5] - 2017-09-27

### Added

- Added `#include <Arduino.h>` to fix `uint32_t` bug

### Changed

## [0.3.4] - 2017-07-31

### Added

### Changed
- Refactored const in many places

- [reverted] double to float on request as float is 99.99% of the
  cases good enough and float(32 bit) is supported in HW for some
  processors.

## [0.3.3] - 2015-03-07

### Added

### Changed

- float -> double to support ARM (compiles)

- moved count() sum() min() max() to .h; for optimizing compiler

## [0.3.2] - 2012-11-10

- minor edits

### Added

- added variance()

### Changed

- changed count -> unsigned long allows for 2^32 samples

## [0.3.1] - 2012-11-10

### Added

### Changed

- minor edits

## [0.3] - 2011-01-07

- branched from 0.2.01 version of Rob Tillaart's code

### Added

### Changed

## [0.2.01] - 2010-10-30

### Added

- added minimum, maximum, unbiased stdev.

### Changed

- changed counter to long -> int overflows @32K samples

## [0.2] - 2010-10-29

### Added

### Changed

- stripped to minimal functionality

## [0.1] - 2010-10-29

- initial version

### Added

### Changed
