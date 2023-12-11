# Change Log DS28CM00

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.0] - 2023-12-11
- refactor API, begin()
- update readme.md
- update examples

----

## [0.3.0] - 2023-09-21
- add Wire1 support for ESP32
- refactored ESP32 interface, no constructor => but a begin()
- add parameter size to **bool getUID(uint8_t \* buffer, uint8_t size = 8)**
- add example **DS28CM00_getUID.ino**
- renamed some internal constants for readability

----

## [0.2.5] - 2022-11.02
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.2.4] - 2021-12-17
- update library.json
- update license
- add isConnected()
- minor edits

## [0.2.3] - 2021-10-26
- update build-CI
- add default Wire in constructor

## [0.2.2] - 2020-12-20
- add Arduino-CI + unit test

## [0.2.1] - 2020-06-07
- fix library.json

## [0.2.0] - 2020-04-11
- refactor
- add #pragma once
- multiple Wire
- ESP support (start)

----

## [0.1.0] - 2017-07-15-  initial version

## [0.1.00]
- initial version




