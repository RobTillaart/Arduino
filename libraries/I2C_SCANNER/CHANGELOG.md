# Change Log I2C_SCANNER

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.1] - 2024-xx-xx
- update examples

## [0.3.0] - 2023-12-05
- remove **begin(sda, scl)** to have less board specific dependencies.

----

## [0.2.1] - 2023-09-24
- fix Wire1 support ESP32
- update keywords.txt

## [0.2.0] - 2023-08-21
- changed interface for **uint16_t ping(address, uint16_t count = 1)**
  - allows multiple tries, for extended diagnosis.
- add example
- update readme.md
- add issue-count badge
- add PlatformIO badge
- minor edits

----

## [0.1.4] - 2022-10-30
- update GitHub actions
- update license 2023
- add experimental **setWireTimeout()**
- minor edit examples

## [0.1.3] - 2022-10-30
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- extend example

## [0.1.2] - 2022-08-30
- elaborate up to useful version

## [0.1.1] - 2022-08-29
- elaborate more

## [0.1.0] - 2022-08-29
- initial version
