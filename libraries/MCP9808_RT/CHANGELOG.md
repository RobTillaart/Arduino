# Change Log MCP9808_RT

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2023-10-04
- Fix #13 Refactor constructor - (simpler)
- removed **setAddress()** - (force one sensor one object)
  as different addresses can have e.g. different offsets.
- add ESP32 specific example.
- Fix #15 PlatformIO badge
-

----

## [0.3.1] - 2023-09-23
- Add Wire1 support for ESP32
- update readme.md

## [0.3.0] - 2023-02-03
- Fix #11 Wire2
- update readme.md
- update GitHub actions
- update license 2023

----

## [0.2.2] - 2022-11-17
- add RP2040 in build-CI
- add changelog.md
- edit readme.md


## [0.2.1] - 2021-12-21
- update library.json
- update license
- minor edits

## [0.2.0] - 2021-11-19
- fix #7 negative temperature

----

## [0.1.4] - 2021-11-08
- update build-CI, badges
- default offset for offset
- default Wire for I2C bus - setAddress()

## [0.1.3] - 2021-01-01
- Arduino-ci + unit test

## [0.1.2] - 2020-11-16
- removed hasAlert
- removed setAlertPin, 
- added 2 alert examples
- refactor low level

## [0.1.1] - 2020-11-12
- refactor

## [0.1.0] - 2020-05-03
- initial version.

