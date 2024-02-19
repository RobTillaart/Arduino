# Change Log lineFormatter

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-02-19
- add **bool setTabs(uint8_t \* arr, uint8_t size)** to add multiple tabs in one call.
- add **uint8_t getTabs(uint8_t \* arr)** get the internal array in one call. Returns size.
- update readme.md
- update examples
- minor edits.

----

## [0.2.1] - 2023-11-07
- update readme.md

## [0.2.0] - 2023-01-30
- add **removeTab(pos)**
- add **existTab(pos)** (prevent double addition).
- made lineCount uint32_t to support long running logs.
- set default parameter 1 for **setAutoNewLine()**
- update unit tests
- update GitHub actions
- update license 2023
- update keywords.txt
- update readme.md
- move code to .cpp

----

## [0.1.5] - 2022-11-14
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md
- minor edits unit tests
- bump version to 0.1.5.
- fix build-CI for examples.

## [0.1.4] - 2021-12-20
- not released (why?)
- update library.json
- update license
- minor edits

## [0.1.3] - 2021-11-06
- update Arduino-CI, badges
- update readme.md
- add reset();

## [0.1.2] - 2020-12-30
- Arduino-ci + unit tests

## [0.1.1] - 2020-06-19
- fix library.json

## [0.1.0] - 2020-05-14
- initial version


