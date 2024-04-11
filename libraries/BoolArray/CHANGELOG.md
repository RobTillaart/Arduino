# Change Log boolArray

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.0] - 2024-04-10
- made BOOLARRAY_MAXSIZE a -D command line define option
- increased default BOOLARRAY_MAXSIZE to 1250 x 8 = 10000 booleans
  - about Arduino UNO max size
- add BoolArray32 class for larger arrays.
- update GitHub actions

----

## [0.2.8] - 2023-02-08
- update readme.md
- optimize begin - test for need to reallocate.

## [0.2.7] - 2023-02-08
- update readme.md
- update GitHub actions
- update license 2023
- move code to .cpp
- improved measurement of performance - boolArrayDemo2.ino

## [0.2.6] - 2022-10-29
- add RP2040 to build-CI
- add changelog.md
- minor edit unit test

## [0.2.5] - 2021-12-12
- update library.json
- license
- minor edits

## [0.2.4] - 2021-10-19
- update build-CI + badges

## [0.2.3] - 2021-01-19
- update readme.md

## [0.2.2] - 2020-12-15
- add arduino-CI + unit tests

## [0.2.1] - 2020-06-05
- fix library.json

## [0.2.0] - 2020-03-29
- #pragma
- update readme.md

----

## [0.1.4] - 2017-07-16
- add masks for performance

## [0.1.3]
- add toggle()

## [0.1.02]
- add error handling

## [0.1.01]
- fix constructor - Thanks WPD64
- error handling

## [0.1.00] - 2015-12-06
- initial version

