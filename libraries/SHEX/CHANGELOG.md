# Change Log SHEX

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.3.3] - 2023-11-21
- update readme.md


## [0.3.2] - 2023-02-20
- fix **flushASCII()**
- fix LIB version number.
- fix command line defines.
- move code from .h to .cpp
- update readme.md
- update GitHub actions
- update license 2023
- minor edits

## [0.3.1] - 2022-11-24
- Add RP2040 support to build-CI.
- Add CHANGELOG.md

## [0.3.0   2022-05-28  breaking!
- change default HEX output instead of pass through.
- add get / setCountDigits() =>
-     #digits of count 4, 6 or 8 (4 = default)
- replaces get / setCounterFlag()
- add define SHEX_COUNTER_DIGITS + SHEX_MIN_LENGTH
- add restartOutput() and getCounter()
- add SHEXA class for ASCII column output
- add SHEXA::flushASCII().

----

## [0.2.3] - 2022-05-28
- add setVTAB(vtab) getVTAB()
- add define SHEX_DEFAULT_VTAB

## [0.2.2] - 2022-05-27
- fix #6 set default length
- add defines SHEX_DEFAULT_LENGTH + SHEX_MAX_LENGTH

## [0.2.1] - 2021-12-28
- update library.json
- update readme.md
- update license
- minor edits

## [0.2.0] - 2021-01-07
- Arduino-CI + unit tests + modifiers

----

## [0.1.1] - 2020-06-19
- fix library.json

## [0.1.0] - 2020-05-24
- initial version

