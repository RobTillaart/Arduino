# Change Log FRAM_I2C
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.5] - 2022-03-23

### Added
- add **uint32_t clear(uint8_t value = 0)**
- add **void setSizeBytes(uint32_t value)**
- added defines for size of known types for e.g. **void setSizeBytes(uint32_t value)**
- add _sizeinBytes private var. Needed in clear a.o.

### Changed
- **getSize()** automatically called in **begin()**
- updated example **FRAM_clear.ino**
- renamed private functions with _
- updated readme.md
-

### Fixed


## [0.3.4] - 2022-03-16

### Added
- add **uint16_t writeObject(memaddr, &obj)** see #13
- add **uint16_t readObject(memaddr, &obj)** see #13
- add examples for write- and readObject()

### Changed
- renamed releaseNotes.md => CHANGELOG.md
- some edits in readme.md

### Fixed


## [0.3.3] - 2022-02-08
- added **getSizeBytes()**
- created releaseNotes.md
- updated readme.md
- add example FRAM_logging.ino

## [0.3.2] - 2021-12-18
- update Arduino-CI,
- add badges in readme.md
- update library.json,
- update license,
- minor edits

## [0.3.1] - 2021-02-05
- fix #7 typo in .cpp

## [0.3.0] - 2021-01-13
- fix #2 ESP32
- add WireN support

## [0.2.3] - 2021-01-11
- fix getMetaData (kudos to PraxisSoft)

## [0.2.2] - 2020-12-23
- add Arduino-CI + unit test
- add **getWriteProtect()**

## [0.2.1] - 2020-06-10
- fix library.json

## [0.2.0] - 2020-04-30
- refactor,
- add writeProtectPin code

## [0.1.1] - 2019-07-31
- added support for Fujitsu 64Kbit MB85RC64T (kudos to ysoyipek)

## [0.1.0] - 2018-01-24
- initial version

