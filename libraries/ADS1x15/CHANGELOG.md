# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [0.3.7] - 2022-06-21

- fix ESP32 Wire.begin datatype


## [0.3.6] - 2022-03-10

### Added
- CHANGELOG.md: moved history in ADS1x15.cpp to this file.
- add default parameters for single channel devices.
  - **readADC(uint8_t pin = 0);**
  - **requestADC(uint8_t pin = 0);**
- two examples for the **ADS1114** (single channel devices)
- update readme.md.

### Changed

### Fixed

## [0.3.5] - 2022-01-21

### Added

### Changed

### Fixed
- fix #36 support for Nano Every

## [0.3.4] - 2021-12-11

### Added
- add unit test constants.

### Changed
- update library.json, license, 
- minor edits incl layout

### Fixed

## [0.3.3] - 2021-10-17

### Added

### Changed
- update build-CI (esp32), readme.md, keywords.txt

### Fixed

## [0.3.2] - 2021-10-07

### Added
- added examples

### Changed
- update readme 

### Fixed
- fix build-CI; 

## [0.3.1] - 2021-04-25

### Added
- add get/setClock() for Wire speed 
- reset()

### Changed

### Fixed
- issue #22

## [0.3.0] - 2021-03-29

### Added
- add Wire parameter to constructors.

### Changed

### Fixed


## OLDER versions

### 0.2.7  - 2020-09-27
- redo readRegister()
- getValue()
- getError()

### [0.2.6] - 2020-09-01
- fix #12
- fix getMaxVoltage
- refactor

### [0.2.5] - 2020-08-26
- add missing readADC_Differential_X_X()

### [0.2.4] - 2020-08-26
- check readme.md and minor fixes

### [0.2.3] - 2020-08-20
- add comparator code
- add async mode

### [0.2.2] - 2020-08-18
- add begin(sda, scl) for ESP32

### [0.2.1] - 2020-08-15
- fix issue #2 gain

### [0.2.0] - 2020-04-08
- initial release; 
- refactor ad fundum;

### [0.1.0] - 2017-07-31
- removed pre 1.0 support; added getVoltage

### [0.0.1] - 2013-03-24
- first working version

### [0.0.0] - 2013-03-24
- initial version



