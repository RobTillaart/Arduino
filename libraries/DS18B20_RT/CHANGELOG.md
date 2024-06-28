# Change Log DS18B20_RT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.2.3] - 2024-06-27
- Fix #32, add connectCheck parameter to getTempC()
- update examples
- update readme.md
- minor edits

## [0.2.2] - 2024-01-03
- fix examples
- extend **OneWireScanner.ino**
- minor edits

## [0.2.1] - 2023-10-19
- update readme.md
- add oneWireScanner.ino example
- add oneWireSearch.ino example
- minor edits

## [0.2.0] - 2023-03-05
- fix #24 - remove resolution parameter from constructor.
- refactor code to keep in sync with DS18B20_INT
- refactor resolution handling
- update readme.md
- minor edits

----

## [0.1.16] - 2023-03-05
- Thanks to SherifMEldeeb.
- Fix issue Infinite loop #22
- Add resolution parameter with constructor.
- Move source files under src/ to comply with PlatformIO dependency system.
- Update library.json
- Update library.properties

## [0.1.15] - 2023-02-22
- fix #20 improve disconnect detection
- add **bool isConnected(uint8_t retries)**
- update keywords.txt
- update readme.md
- minor edits

## [0.1.14] - 2023-02-03
- update readme.md
- add **getResolution()**
- move code from .h to .cpp.
- minor refactor
- update keywords
- update GitHub actions
- update license 2023

## [0.1.13] - 2022-11-02
- add changelog.md
- add rp2040 to build-CI
- update unit test constants

## [0.1.12] - 2021-12-17
- update library.json
- update license
- minor edits

## [0.1.11] - 2021-10-03
- add dependency
- fix build-CI

## [0.1.10] - 2021-06-14
- add retries parameter to begin()

## [0.1.9] - 2021-05-26
- add oneWire.reset() in begin()

## [0.1.8] - 2021-04-08
- clear scratchpad before read
- update readme.md

## [0.1.7] - 2020-12-20
- add Arduino CI + unit test

## [0.1.6] - 2020-06-07
- fix library.json

## [0.1.5] - 2020-04-29
- #4 added set/getConfig 
- add DEVICE_CRC_ERROR
- add example

## [0.1.4] - 2020-04-23
- #2 add retry in begin() to support Wemos

## [0.1.3] - 2020-04-22
- #1 fix library.json file

## [0.1.2] - 2020-04-11
- #pragma once
- refactor

## [0.1.1] - 2020-02-18
- added getAddress()

## [0.1.0] - 2017-07-25
- initial version

