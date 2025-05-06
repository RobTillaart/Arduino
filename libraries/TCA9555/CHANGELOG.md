# Change Log TCA9555

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.3] - 2025-05-05
- updated examples after HW test
- add TCA9555_blink.ino
- add TCA9555_performance.ino
- minor edits 

## [0.4.2] - 2025-04-17
- update readme.md
- add derived class CAT9555

## [0.4.1] - 2025-01-12
- fix **begin()** mode parameter (thanks to CrispyPyro)
- update readme.md.
- add derived classes PCA9555 and PCA9535

## [0.4.0] - 2025-01-09
- sync with TCA9554
- add begin(mode, mask)
- add keywords.txt
- fix interrupt example
- update readme.md

----

## [0.3.2] - 2024-03-11
- Fix #18, pinMode in examples (kudos to nerdyscout)
- update GitHub actions to v4
- update readme.md
- add **TCA9555_interrupt.ino** to be verified
- add datasheet to repo
- minor edits

## [0.3.1] - 2024-01-06
- minor edits

## [0.3.0] - 2023-12-23
- Fix #14, support for Arduino ESP32 S3 - breaking change
- update readme.md
- update examples.

----

## [0.2.0] - 2023-12-08
- refactor API, begin()
- update readme.md
- update examples.

----

## [0.1.7] - 2023-11-22
- update readme.md

## [0.1.6] - 2023-09-23
- add Wire1 support for ESP32
- update readme.md

## [0.1.5] - 2022-12-30
- add pin numbers TCA_P00 -- TCA_P17
- add **uint8_t getType()** + example
- update unit test

## [0.1.4] - 2022-12-29
- Fix #7 missing public:
- add unit test for TCA9535 constructor
- add examples for TCA9535
- update examples
- add **getAddress()** (debugging)
- update readme.md
- update GitHub actions -> v3

## [0.1.3] - 2022-11-25
- Add RP2040 support to build-CI.
- Add CHANGELOG.md
- update readme.md


## [0.1.2] - 2021-12-28
- update Arduino-CI
- update readme.md
- update license
- minor edits

## [0.1.1] - 2021-06-10
- add 16 bit interface


## [0.1.0] - 2021-06-09
- initial version

