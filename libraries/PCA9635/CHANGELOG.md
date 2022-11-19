# Change Log PCA9635

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).



## [0.4.2] - 2022-11-19
- add RP2040 in build-CI
- add changelog.md

## [0.4.1 - 2022-09-10
- Fix #17 adjust begin() interface for ESP32

## [0.4.0] - 2022-05-29
- breaking changes
- rename reset() to configure()
- add mode1 and mode2 parameter to configure.
- add SUB CALL and ALL CALL functions.
- update documentation.
- renamed PCA9634_MODE2_STOP to PCA9634_MODE2_ACK
- add mode parameters to begin()

----

## [0.3.4] - 2022-04-13
- add constants and functions for mode registers.

## [0.3.3] - 2022-01-03
- add channelCount()

## [0.3.2] - 2021-12-23
- update library.json, readme, license, minor edits

## [0.3.1] - 2021-04-25
- fix writeN by aspyra

## [0.3.0] - 2021-01-18
- support Wire1..WireN

----

## [0.2.2] - 2021-01-13
- refactor
- fix register index error

## [0.2.1] - 2021-01-05
- Arduino-CI + unit test

## [0.2.0] - 2020-05-26
- major refactor
- ESP32 support

----

## [0.1.2] - 2020-05-07
- fix for PCA9635_MODE1

## [0.1.1] - 2016-04-24
- set autoincr in constructor

## [0.1.0] - 2016-04-23
- initial BETA version


