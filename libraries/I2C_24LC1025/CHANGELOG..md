# Change Log I2C_24LC1025
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2023-11-24
- simplify **begin()**, remove setting Wire pins from library.
- add **getAddress()**
- update readme.md
- update examples
- changed version string to I2C_24LC1025_LIB_VERSION

----

## [0.2.5] - 2023-09-09
- Sync I2C_EEPROM
- add writeProtectPin as optional parameter in **begin()**
- add **bool hasWriteProtectPin()**
- add **void allowWrite()**
- add **void preventWrite()**
- add **void setAutoWriteProtect(bool b)**
- add **bool getAutoWriteProtect()**
- optimized **waitEEReady()**
- update keywords.txt
- update readme.md

## [0.2.4] - 2023-05-11
- redo support for RP2040 
  - see issue #53 / #55 I2C_EEPROM

## [0.2.3] - 2023-05-02
- improve support for RP2040
- move code from .h to .cpp
- update readme.md
- minor edits

## [0.2.2]
- add changelog.md
- add RP2040 to build-CI
- minor edits

## [0.2.1] - 2022-06-11
- update documentation
- minor edits
- minor improvements / bug fixes
- add get/setExtraWriteCycleTime()

## [0.2.0] - 2022-06-08
- add verify functions
- improve documentation / comments

----

## [0.1.5] - 2021-08-30
- fix #3 I2C_DEVICESIZE_24LC512 => I2C_DEVICESIZE_24LC1025

## [0.1.4] - 2021-05-27
- fix library.properties

## [0.1.6] - 2021-12-19
- update library.json
- update license
- minor edits

## [0.1.3] - 2021-02-02
- add updateBlock()

## [0.1.2] - 2021-01-31
- fix reading over 64K block border

## [0.1.1] - 2021-01-20
- major redo

## [0.1.0] - 2019-12-11
- initial version (not tested)


