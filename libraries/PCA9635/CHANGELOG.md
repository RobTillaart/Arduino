# Change Log PCA9635

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.0] - 2024-01-18
- fix #32, setLedDriverMode(uint8_t mode)
- minor edits (examples)

----

## [0.5.0] - 2023-12-11
- refactor API, begin()
- add **uint8_t getAddress()**
- update readme.md
- update examples

----

## [0.4.7] - 2023-09-24
- add Wire1 support for ESP32
- update readme.md
- minor edits

## [0.4.6] - 2023-05-24
- renaming #defines PCA963X... to prepare merge with PCA9634.
  - old defines will work until next major release
- update keywords.txt

## [0.4.5] - 2023-04-26
- add **writeLedOut(reg, mask)** experimental
- add **readLedOut(reg)** experimental
- add **setLedDriverMode(mode)** experimental
- add example PCA9635_shift_rotate.ino
- start renaming #defines PCA963X... to prepare merge with PCA9634.
  - old defines will work until next major release
- add **writeN_noStop** and **writeStop** (from PCA9634)
- move code from .h to .cpp
- reorder + refactor code
- update readme.md
- minor edits

## [0.4.4] - 2023-01-23
- fix #22 update documentation
- add **I2C_SoftwareReset()** experimental

## [0.4.3] - 2023-01-23
- update GitHub actions
- update license 2023
- add OutputEnable control functions.
- add example **PCA9635_OE_control.ino**
- update unit test.
- **configure()** now returns error state
- update readme.md
- minor edits

## [0.4.2] - 2022-11-19
- add RP2040 in build-CI
- add changelog.md

## [0.4.1 - 2022-09-10
- Fix #17 adjust begin() interface for ESP32

## [0.4.0] - 2022-05-29
- breaking changes
- rename reset() to configure()
- add mode1 and mode2 parameter to configure.
- add SUB CALL and ALL CALL functions.
- update documentation.
- renamed PCA9634_MODE2_STOP to PCA9634_MODE2_ACK
- add mode parameters to begin()

----

## [0.3.4] - 2022-04-13
- add constants and functions for mode registers.

## [0.3.3] - 2022-01-03
- add channelCount()

## [0.3.2] - 2021-12-23
- update library.json, readme, license, minor edits

## [0.3.1] - 2021-04-25
- fix writeN by aspyra

## [0.3.0] - 2021-01-18
- support Wire1..WireN

----

## [0.2.2] - 2021-01-13
- refactor
- fix register index error

## [0.2.1] - 2021-01-05
- Arduino-CI + unit test

## [0.2.0] - 2020-05-26
- major refactor
- ESP32 support

----

## [0.1.2] - 2020-05-07
- fix for PCA9635_MODE1

## [0.1.1] - 2016-04-24
- set autoincr in constructor

## [0.1.0] - 2016-04-23
- initial BETA version


