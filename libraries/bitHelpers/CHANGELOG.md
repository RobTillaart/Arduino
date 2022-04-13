# Change Log bitHelpers

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.7] - 2022-04-13

### Added

### Changed
- updated **bitRot()** by faster version and made the old one a ref version
  - replaced one random call with mod (faster)
  - has a times parameter to apply bitrot n times.

### Fixed
- **bitRotateRight(value, pos)** handles pos == 0 separately.
- **bitRotateLeft(value, pos)** handles pos == 0 separately.


## [0.1.6] - 2022-04-11

### Added
- add CHANGELOG.md
- add experimental **bitRotFast()** to replace **bitRot()** in a next release

### Changed
- better masking in **bitCount()**
- added () in several places.
- edit README.md

### Fixed
- Issue #10 Incorrect behaviour in bitWrite64 for value 31
  Specific for ESP8266
- Fix **bitRead64()** return value.


## [0.1.5] - 2021-12-14

### Changed
- update library.json, license, minor edits


## [0.1.4] - 2021-10-19

### Changed 
- update build-CI (e.g. ESP32 compilation of tests)
- update README.md with badges


## [0.1.3] - 2021-08-09

### Changed
- update README.md
- update unit tests


## [0.1.2] - 2020-12-14

### Added
- add Arduino-CI + unit tests


## [0.1.1] - 2020-08-10

### Added
- added BitsNeeded, bitSet64 family


## [0.1.0] - 2020-07-29

### Added
- initial release


## [0.0.1] - 2015-11-07

### Added
- initial version






