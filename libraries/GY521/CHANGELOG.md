# Change Log GY521

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.6.1] - 2024-07-25
Co-authored-by: Maik Menz 
- redo of **calibrate()** function, Kudos to Maik Menz.
- Fix #59 Added orientation arguments to calibrate function (#59)
- Fix #57 calibration error scaling
- update library.json
- improve initialization of gax, gay and gaz
- add **readRaw()** to improve calibrate()
- update readme.md 
- improve initialization


## [0.6.0] - 2024-06-22
- fix #54, calibrate() function, Kudos to jens-kuerten and MArimont3
- minor edits

----

## [0.5.3] - 2024-05-08
- fix #52, add **uint8_t getAddrress()**
- fix #51, add **bool setDLPFMode(uint8_t mode)** and **uint8_t getDLPFMode()**
- add const float GRAVITY=9.80655;
- minor edits

## [0.5.2] - 2024-01-16
- fix #48, use float variables in example GY521_test_1.ino
- add **void calibrate(uint16_t times)** to API
- add **GY521_performance_calibrate.ino** example
- add **GY521_raw_cooked.ino** example
- make explicit that pitch roll yaw is work in progress.
- update readme.md
  - calibrate section
  - add some tables
- minor edits in examples

## [0.5.1] - 2023-12-11
- redo initialization order.

## [0.5.0] - 2023-12-05
- refactor API, begin()
- update readme.md

----

## [0.4.1] - 2023-11-02
- update readme.md
- minor edits

## [0.4.0] - 2023-06-11
- fix #42 roll + pitch "jumps" after full rotation.
- fixed normalization code.
- made normalization conditional
  - add **void setNormalize(bool normalize = true)**
  - add **bool getNormalize()**
- update readme.md
- minor edits

----

## [0.3.9] - 2023-01-27
- update GitHub actions
- update license 2023
- edit changelog.md
- update readme.md
- minor edits

## [0.3.8] - 2022-10-07
- added CHANGELOG.md
- fix #36 - limit values of pitch() roll() yaw() to 0..360 range.
- rename three constants, move to .h.
  - add constants check to unit test.
  - updated keywords
- updated build to include RP2040 pico
- updated documentation a bit.

## [0.3.7] - 2022-07-26
- add partial reads readAccel(), readGyro() and readTemperature()
- rename + add GY521_LIB_VERSION to examples.

## [0.3.6] - 2021-12-18
- update library.json, license, minor edits

## [0.3.5] - 2021-10-20
- update build-CI, badges
- fix #28 add wakeup to begin().

## [0.3.4] - 2021-07-12
- fix #24 improve precision

## [0.3.3] - 2021-07-05
- fix #22 improve maths

## [0.3.2] - 2021-07-05
- fix #20 support multiWire

## [0.3.1] - 2021-06-13
- added more unit test
- some initialization

## [0.3.0] - 2021-04-07
- fix #18 acceleration error correction (kudo's to Merkxic)

----

## [0.2.3] - 2021-01-26
- align version numbers (oops)

## [0.2.2] - 2021-01-24
- add interface part to readme.md
- add GY521_registers.h

## [0.2.1] - 2020-12-24
- add Arduino-CI build
- add unit tests

## [0.2.0] - 2020-11-03
- improve error handling

----

## [0.1.5] - 2020-09-29
- fix #6 fix maths for Teensy

## [0.1.4] - 2020-09-29
- fix #5 missing ;

## [0.1.3] - 2020-08-07
- fix ESP support
- add pitch roll yaw demo

## [0.1.2] - 2020-08-06
- fix setAccelSensitivity
- add getters

## [0.1.1] - 2020-07-09
- refactor
- initial release

## [0.1.0] - 2017-11-20
- initial version

