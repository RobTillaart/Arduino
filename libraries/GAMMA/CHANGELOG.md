# Change Log Gamma

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [0.4.1] - 2023-10-26
- update readme.md


## [0.4.0] - 2023-01-26
- optimize **setGamma()** especially for ESP32
- optimize **get[]**  especially for ESP32
- update GitHub actions
- update license 2023
- update readme.md

----

## [0.3.1] - 2022-11-08
- add changelog.md
- add rp2040 to build-CI
- update readme.md

## [0.3.0] - 2022-07-26
- change return type begin() + setGamma()
- add test gamma <=0 in setGamma()
- add _table == NULL tests
- fixed type of index in [] operator.
- adjust rounding in setGamma() to minimize errors.
- update build-CI

----

## [0.2.2   2022-07-25
- split in .h and .cpp
- add Stream parameter to dump()
- add dumpArray(Stream)
- fix distinct()

## [0.2.1   2021-12-18
- update library.json, license,
- add constants, minor edits.

## [0.2.0   2021-11-02
- update build-CI, badges
- add begin() - fixes ESP32 crash.

----

## [0.1.1] - 2020-12-24
- Arduino-CI + unit test

## [0.1.0] - 2020-08-08
- initial release

