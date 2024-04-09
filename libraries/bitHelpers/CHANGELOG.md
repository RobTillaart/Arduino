# Change Log bitHelpers

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.1.12] - 2024-04-09
- update GitHub actions
- update keywords.txt
- minor edits


## [0.1.11] - 2023-10-18
- update readme.md

## [0.1.10] - 2023-02-08
- reorganize readme.md
- update GitHub actions
- update license 2023

## [0.1.9] - 2022-10-29
- add RP2040 to build-CI
- simplified changelog.md
- minor edit unit test
- add printHelpers lib in build-CI

## [0.1.8] - 2022-04-13
- split bitHelpers.h file into a .h and a .cpp file to prevent multiple declarations in some complexer projects.

## [0.1.7] - 2022-04-13
- updated **bitRot()** by faster version and made the old one a ref version
  - replaced one random call with mod (faster)
  - has a times parameter to apply bitrot n times.
- **bitRotateRight(value, pos)** handles pos == 0 separately.
- **bitRotateLeft(value, pos)** handles pos == 0 separately.

## [0.1.6] - 2022-04-11
- add CHANGELOG.md
- add experimental **bitRotFast()** to replace **bitRot()** in a next release
- better masking in **bitCount()**
- added () in several places.
- edit README.md
- Issue #10 Incorrect behaviour in bitWrite64 for value 31  Specific for ESP8266
- Fix **bitRead64()** return value.

## [0.1.5] - 2021-12-14
- update library.json
- update license
- minor edits

## [0.1.4] - 2021-10-19
- update build-CI (e.g. ESP32 compilation of tests)
- update README.md with badges

## [0.1.3] - 2021-08-09
- update README.md
- update unit tests

## [0.1.2] - 2020-12-14
- add Arduino-CI + unit tests

## [0.1.1] - 2020-08-10
- add BitsNeeded
- add bitSet64 family

## [0.1.0] - 2020-07-29
- initial release

## [0.0.1] - 2015-11-07
- initial version

