# Change Log SHT85

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.0] - 2023-12-09
- refactor API, move parameters from begin() to constructor
- update readme.md
- update examples
- minor edits

----

## [0.5.1] - 2023-09-21
- fix #21, again ...

## [0.5.0] - 2023-09-21
- fix #21, support Wire1 for ESP32
- move TwoWire selection to constructor.
- update readme.md

----

## [0.4.2] - 2023-09-05
- fix #19 SHT85 cannot be address 0x45
- rewrote begin()
- removed example SHT85_duo
- add example SHT85_multiplex
- add section about multiple SHT85 to readme.md
- redo badges in readme.md
- minor edits

## [0.4.1] - 2022-05-09
- add **uint32_t getSerialNumber()** for SHT85 (no CRC check).
- improve error handling.
- update readme.md

## [0.4.0] - 2022-12-14
- redo asynchronous interface
- add **uint32_t getLastRequest()** timestamp.
- add offset functions for temperature and humidity.
- update readme.md
- move code from .h to .cpp
- updated unit test
- add examples
- update keywords.txt
- update GitHub actions
- update license 2023
- minor edits

----

## [0.3.3] - 2022-11-24
- Add RP2040 support to build-CI.
- Add CHANGELOG.md

## [0.3.2] - 2022-01-17
- fix #8 add SHT_DEFAULT_ADDRESS + 2x begin()

## [0.3.1] - 2021-12-28
- update library.json
- update readme.md
- update license
- minor edits

## [0.3.0] - 2021-10-20
- Fix #6 image in documentation,
- pdate build-CI

----

## [0.2.0] - 2021-08-24
- split off base class
- create derived classes SHT85, 30, 31, 35

----

## [0.1.4] - 2021-08-24
- prevent heater to switch on too fast.
- update readme

## [0.1.3] - 2021-08-06
- expose raw data from sensor

## [0.1.2] - 2021-05-27
- fix Arduino-lint

## [0.1.1] - 2021-03-13
- initial release

## [0.1.0] - 2021-02-10
- initial version

